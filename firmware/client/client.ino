/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        client.ino                                   Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 21:32:04 by rFeijo                                              */
/*        Updated: 2022/05/01 15:34:54 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include "config.h"
#include "system.h"

tractian_system_t sys;

uint16_t counter = SYSTEM_COUNTER;

void setup(void) {
  sys.init_serial_console(SYSTEM_BAUD_RATE);
  sys.serial_print("Main - System Initialized");

  if (sys.mount_spiffs())
    sys.serial_print("SPIFFS - Memory ready");
  else
    ESP.restart();

  if (sys.init_rf_transceiver(NRF24L01_CHANNEL, NRF24L01_DATA_RATE, NRF24L01_TX_POWER))
    sys.serial_print("RF - Client ready");
  else
    ESP.restart();
}

void loop(void) {
  if (counter == SYSTEM_COUNTER) {
    sys.send_message();
    
    counter = 0;
  }
 
  ESP.deepSleep(SYSTEM_INTERVAL);

  counter++;
}
