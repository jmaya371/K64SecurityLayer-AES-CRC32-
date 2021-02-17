/*
 * SecurityLayer_cfg.h
 *
 * brief:
 * DESCRIPCION DE MACROS, TIPOS Y CONSTANTES DE CONFIGURACION EXCLUSIVOS PARA EL COMPONENTE SecurityLayer
 *
 *  Created on: 17 feb. 2021
 *      Author: josue
 */

#ifndef SECURITYLAYER_SECURITYLAYER_CFG_H_
#define SECURITYLAYER_SECURITYLAYER_CFG_H_



/*system headers*/

/*Used headers*/

/*Own headers*/


/*Private Constants*/
#define SecurityLayer_PRIVATE_KEY_cfg { 		\
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,	\
0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06	\
}

#define SecurityLayer_INIT_IV_cfg {				\
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 	\
}
/*Private Macros*/

/*Private Types*/


#endif /* SECURITYLAYER_SECURITYLAYER_CFG_H_ */
