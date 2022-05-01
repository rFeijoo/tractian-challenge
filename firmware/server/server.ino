/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        server.ino                                   Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 16:47:51 by rFeijo                                              */
/*        Updated: 2022/04/30 19:25:25 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include "config.h"
#include "system.h"

tractian_system_t sys;

void(* resetFunc) (void) = 0;

void setup(void) {
  sys.init_serial_console(SYSTEM_BAUD_RATE);
  sys.serial_print("Main - System Initialized");

  if (sys.init_rf_transceiver(NRF24L01_CHANNEL, NRF24L01_DATA_RATE, NRF24L01_TX_POWER))
    sys.serial_print("RF - Server ready");
  else
    resetFunc();
}

void loop(void) {
  if (sys.check_for_new_messages())
    sys.process_new_msg();
}
