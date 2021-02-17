/*
 * ApplicationLayer.h
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */

#ifndef APPLICATIONLAYER_APPLICATIONLAYER_H_
#define APPLICATIONLAYER_APPLICATIONLAYER_H_

/*Used headers*/

/*Own headers*/


/*Public Variables*/

/*Public Functions*/
extern void ApplicationLayer_vReceive(uint8_t* pu8Msg, uint16_t u16LenBuff);
extern void ApplicationLayer_vTransmit(void* pvEncryptMsg);

#endif /* APPLICATIONLAYER_APPLICATIONLAYER_H_ */
