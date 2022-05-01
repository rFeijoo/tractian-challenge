/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        system.h                                     Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 16:47:51 by rFeijo                                              */
/*        Updated: 2022/04/30 19:25:25 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include <Arduino.h>
#include "config.h"
#include <SPI.h>
#include <RH_NRF24.h>

#ifndef _SYSTEM_H_
  #define _SYSTEM_H_

class tractian_system_t {
  public:
    void    init_serial_console(uint16_t baud_rate);
    
    void    init_digital_output(uint8_t pin, bool state);
    void    toggle_digital_output(uint8_t pin);

    bool    init_rf_transceiver(uint8_t ch, RH_NRF24::DataRate d_rate, RH_NRF24::TransmitPower tx_power);
    bool    check_for_new_messages(void);
    String  process_new_msg(void);
    
    void serial_print(String msg);
};

#endif /*_SYSTEM_H_*/
