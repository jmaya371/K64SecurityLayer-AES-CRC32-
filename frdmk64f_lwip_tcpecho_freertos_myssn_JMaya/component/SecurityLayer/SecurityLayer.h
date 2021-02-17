/*
 * SecurityLayer.h
 *
 * brief:
 * DESCRIPCION DE PROTOTIPOS DE INTERFACES QUE EXPORTA EL COMPONENTE SecurityLayer
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */

#ifndef SECURITYLAYER_SECURITYLAYER_H_
#define SECURITYLAYER_SECURITYLAYER_H_



/*system headers*/
#include <stdint.h>

/*Used headers*/

/*Own headers*/
#include "SecurityLayer_def.h"

/*Public Variables*/

/*Public Functions*/
extern void SecurityLayer_vTransmit(uint8_t* pu8Buff, void* pvEncryptMsg);
extern int32_t SecurityLayer_s32Receive(void* pvBuff, uint16_t u16Len);

#endif /* SECURITYLAYER_SECURITYLAYER_H_ */
