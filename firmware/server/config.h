/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        config.h                                     Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 16:47:51 by rFeijo                                              */
/*        Updated: 2022/04/30 19:25:25 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include <RH_NRF24.h>

#ifndef _CONFIG_H_
  #define _CONFIG_H_

/* 
 *  Diretivas de configuração geral do firmware
 */
#define SYSTEM_DEBUG_MODE_ON

#define SYSTEM_BAUD_RATE  9600
#define SERIAL_INIT_COM   "\r\n"

#define NRF24L01_CHANNEL    1
#define NRF24L01_DATA_RATE  RH_NRF24::DataRate2Mbps
#define NRF24L01_TX_POWER   RH_NRF24::TransmitPower0dBm
#define NRF24L01_DELAY      2000

#endif /*_CONFIG_H_*/
