/*
 * SecurityLayer.c
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */


/*system headers*/
#include <stdint.h>
#include <err.h>
#include "MK64F12.h"

/*Used headers*/
#include "aes.h"
#include "fsl_crc.h"
#include "fsl_debug_console.h"

/*Own headers*/
#include "SecurityLayer_cfg.h"
#include "SecurityLayer_def.h"
#include "SecurityLayer.h"

/*Private Variables*/
const static uint8_t SecurityLayer_s_au8PrivateKey[] = SecurityLayer_PRIVATE_KEY_cfg;

/*Private Functions*/
static void SecurityLayer_vInitCrc32(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial         = 0x04C11DB7U;
    config.seed               = seed;
    config.reflectIn          = true;
    config.reflectOut         = true;
    config.complementChecksum = true;
    config.crcBits            = kCrcBits32;
    config.crcResult          = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

static void SecurityLayer_s_vPrintText(uint8_t* pu8Buff, uint16_t u16LenBuff)
{
	PRINTF("Hexadecimal Message: \r\n");
	for(int i=0; i<u16LenBuff; i++) {
		PRINTF("0x%02x,", pu8Buff[i]);
	}
	PRINTF("\r\n");
	PRINTF("Char Message: \r\n");
	for(int i=0; i<u16LenBuff; i++) {
		PRINTF("%c,", pu8Buff[i]);
	}
	PRINTF("\r\n\n");
}

static uint32_t SecurityLayer_s_u32GetCRC32(void* pvAligMsg, uint16_t u16AligLenMsg)
{
	CRC_Type *stCRCbase = CRC0;
	uint32_t checksum32;

	SecurityLayer_vInitCrc32(stCRCbase, 0xFFFFFFFFU);
    CRC_WriteData(stCRCbase, (uint8_t *)pvAligMsg, u16AligLenMsg);
    checksum32 = CRC_Get32bitResult(stCRCbase);

    PRINTF("CRC-32: 0x%08x\r\n", checksum32);

    return checksum32;
}

/*Public Functions*/
void SecurityLayer_vTransmit(uint8_t* pu8Buff, void* pvEncryptMsg)
{
	uint8_t iv[]  = SecurityLayer_INIT_IV_cfg;
	uint16_t u16LenBuff = 0U;
	uint16_t u16AligLenBuff = 0U;
	uint8_t au8AligMsg[512] = {0};
	uint32_t u32CRC32 = 0U;
	AES_ctx stAESctx;
	SecurityLayer_tstAllMsg* pstEncryptedMsg = (SecurityLayer_tstAllMsg*)pvEncryptMsg;

	/* Init the AES context structure */
	AES_init_ctx_iv(&stAESctx, SecurityLayer_s_au8PrivateKey, iv);

	/* To encrypt an array its lenght must be a multiple of 16 so we add zeros */
	u16LenBuff = strlen(pu8Buff);
	u16AligLenBuff = u16LenBuff + (16 - (u16LenBuff%16) );
	memcpy(au8AligMsg, pu8Buff, u16LenBuff);
	pstEncryptedMsg->u16LenBuff = u16AligLenBuff;

	AES_CBC_encrypt_buffer(&stAESctx, au8AligMsg, u16AligLenBuff);

	for(int i=0; i<u16AligLenBuff; i++) {
		pstEncryptedMsg->au8BuffMsg[i] = au8AligMsg[i];
	}

	PRINTF("Plain-Text Message: \r\n");
	SecurityLayer_s_vPrintText(pu8Buff, u16LenBuff);
	PRINTF("Encrypted Message: \r\n");
	SecurityLayer_s_vPrintText(au8AligMsg, u16AligLenBuff);

	pstEncryptedMsg->u32CRC32 = 0x0000;
	u32CRC32 = SecurityLayer_s_u32GetCRC32((void*)pstEncryptedMsg, (sizeof(u32CRC32)+sizeof(u16LenBuff)+u16AligLenBuff));
	pstEncryptedMsg->u32CRC32 = u32CRC32;
}

int32_t SecurityLayer_s32Receive(void* pvBuff, uint16_t u16Len)
{
	uint8_t iv[]  = SecurityLayer_INIT_IV_cfg;
	uint16_t u16LenBuff = 0U;
	uint16_t u16AligLenBuff = 0U;
	uint8_t au8AligMsg[512] = {0};
	AES_ctx stAESctx;
	uint32_t u32CRC32 = 0U;
	uint32_t u32CRC32BuffMsg = 0U;
	uint32_t u32Return = ERR_BUF;
	SecurityLayer_tstAllMsg* pstBuff = pvBuff;

	if ((pstBuff != NULL) || (u16Len != sizeof(pstBuff)) || (pstBuff->u16LenBuff != 0))
	{
		u32CRC32BuffMsg = pstBuff->u32CRC32;
		pstBuff->u32CRC32 = 0U;
		u32CRC32 = SecurityLayer_s_u32GetCRC32(pstBuff, u16Len);
		pstBuff->u32CRC32 = u32CRC32;

		if (u32CRC32 != u32CRC32BuffMsg)
		{

		}
		else
		{
			/* Init the AES context structure */
			AES_init_ctx_iv(&stAESctx, SecurityLayer_s_au8PrivateKey, iv);

			/* To encrypt an array its lenght must be a multiple of 16 so we add zeros */
			u16LenBuff = sizeof(pstBuff->au8BuffMsg);
			u16AligLenBuff = u16LenBuff + (16 - (u16LenBuff%16) );
			memcpy(au8AligMsg, pstBuff->au8BuffMsg, u16LenBuff);

			AES_CBC_decrypt_buffer(&stAESctx, au8AligMsg, u16AligLenBuff);
			PRINTF("Encrypted Message: \r\n");
			SecurityLayer_s_vPrintText(pstBuff->au8BuffMsg, pstBuff->u16LenBuff);
			u32Return = ERR_OK;

			ApplicationLayer_vReceive(au8AligMsg, pstBuff->u16LenBuff);
		}
	}
	return u32Return;
}
