/*
 * ApplicationLayer.c
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */

/*system headers*/
#include <stdint.h>
#include <err.h>
#include "MK64F12.h"

/*Used headers*/
#include "SecurityLayer_def.h"
#include "SecurityLayer.h"

/*Own headers*/
#include "ApplicationLayer_cfg.h"
#include "ApplicationLayer_def.h"
#include "ApplicationLayer.h"

/*Private Variables*/
static uint8_t ApplicationLayer_s_u8SelMsg = 0U;
static uint8_t* vData;
/*Private Functions*/
static void* ApplicationLayer_pvSelectMsg(void)
{
	if (ApplicationLayer_s_u8SelMsg ==enMsg1)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_1;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg2)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_2;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg3)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_3;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg4)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_4;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg5)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_5;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg6)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_6;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg7)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_7;
	}
	else if (ApplicationLayer_s_u8SelMsg ==enMsg8)
	{
		vData = (uint8_t*) ApplicationLaye_MSG_8;
	}
	else
	{

	}

	ApplicationLayer_s_u8SelMsg = (ApplicationLayer_s_u8SelMsg + 1)%enTotalMsg;

	return vData;
}
/*Public Functions*/
void ApplicationLayer_vReceive(uint8_t* pu8Msg, uint16_t u16LenBuff)
{
	PRINTF("Plain-Text Message: \r\n");
	PRINTF("Hexadecimal Message: \r\n");
	for(int i=0; i<u16LenBuff; i++) {
		PRINTF("0x%02x,", pu8Msg[i]);
	}
	PRINTF("\r\n");
	PRINTF("Char Message: \r\n");
	for(int i=0; i<u16LenBuff; i++) {
		PRINTF("%c,", pu8Msg[i]);
	}
	PRINTF("\r\n\n");
}

void ApplicationLayer_vTransmit(void* pvEncryptMsg)
{
	uint8_t* au8MsgToSend = ApplicationLayer_pvSelectMsg();

	SecurityLayer_vTransmit(au8MsgToSend, pvEncryptMsg);
}
