/*
 * SecurityLayer_def.h
 *
 * brief:
 * DESCRIPCION DE MACROS, TIPOS Y CONSTANTES DE CONFIGURACION QUE EXPORTA EL COMPONENTE SecurityLayer
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */

#ifndef SECURITYLAYER_SECURITYLAYER_DEF_H_
#define SECURITYLAYER_SECURITYLAYER_DEF_H_



/*system headers*/

/*Used headers*/

/*Own headers*/



/*Public Constants*/
#define SecurityLayer_nSizeOfCRCBytes		(4U)
#define SecurityLayer_nSizeOfLenMsgBytes	(2U)
/*Public Macros*/
#define SecurityLayer_CalcSize(SizeMsg)		(SecurityLayer_nSizeOfCRCBytes+SecurityLayer_nSizeOfLenMsgBytes+SizeMsg)
/*Public Types*/
typedef struct
{
	uint32_t u32CRC32;
	uint16_t u16LenBuff;
	uint8_t au8BuffMsg[512];
}SecurityLayer_tstAllMsg;

#endif /* SECURITYLAYER_SECURITYLAYER_DEF_H_ */
