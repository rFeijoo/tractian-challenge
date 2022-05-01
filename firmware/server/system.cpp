/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        system.cpp                                   Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 16:47:51 by rFeijo                                              */
/*        Updated: 2022/04/30 19:25:25 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include "system.h"

RH_NRF24 transceiver;

/** 
 * @brief Inicializa o Serial Console, quando com o modo DEBUG ativado.
 *
 * @param baud_rate Taxa de transmissão do Serial Console.
 */
void tractian_system_t::init_serial_console(uint16_t baud_rate) {
  #ifdef SYSTEM_DEBUG_MODE_ON
    Serial.begin(baud_rate);
  
    while (!Serial)
      ;
  
    Serial.print(SERIAL_INIT_COM);
  #endif /*SYSTEM_DEBUG_MODE_ON*/
}

/** 
 * @brief Inicializa um GPIO como saída digital.
 *
 * @param pin GPIO a ser inicializado como saída digital.
 * @param state Estado inicial do GPIO configurado.
 */
void tractian_system_t::init_digital_output(uint8_t pin, bool state) {
  pinMode(pin, OUTPUT);

  digitalWrite(pin, state);

  serial_print("GPIO - Pin " + String(pin) + " initialized as digital output");
}

/** 
 * @brief Inverte o estado de um pino tipo saída digital.
 *
 * @param pin GPIO a ser invertido.
 */
void tractian_system_t::toggle_digital_output(uint8_t pin) {
  bool state = digitalRead(pin);

  if (state)
    digitalWrite(pin, LOW);
  else
    digitalWrite(pin, HIGH);
}

/** 
 * @brief Inicializa o módulo nRF24L01+.
 * 
 * @param ch Canal do módulo (por padrão, inicializado no canal 2).
 * @param d_rate Taxa de transmissão, em kbps.
 * @param tx_power Potência de transmissão, em dBm.
 * 
 * @return:
 *    - true:  Inicialização concluída com sucesso.
 *    - false: Falha na inicialização.
 */
bool tractian_system_t::init_rf_transceiver(uint8_t ch, RH_NRF24::DataRate d_rate, RH_NRF24::TransmitPower tx_power) {
  bool status = true;
  
  if (!transceiver.init()) {
    serial_print("RF - Failed to initialize nRF24L01+");
    status = false;
  }

  if (!transceiver.setChannel(ch)) {
    serial_print("RF - Failed to configure nRF24L01+ channel");
    status = false;
  }

  if (!transceiver.setRF(d_rate, tx_power)) {
    serial_print("RF - Failed to configure nRF24L01+ RX/TX");
    status = false;
  }

  delay(NRF24L01_DELAY);

  return (status);
}

/*
 * @brief Verifica se há alguma nova mensagem recebida pelo módulo nRF24L01+.
 * 
 * @return:
 *    - true:  Nova mensagem recebida.
 *    - false: Nenhum nova mensagem recebida.
 */
bool tractian_system_t::check_for_new_messages(void) {
  if (transceiver.available()) {
    serial_print("RF - New message received");
    return (true);
  }

  return (false);
}

/* 
 *  @brief Processa novas mensagens recebidas pelo módulo nRF24L01+.
 *  
 *  @
 */
String tractian_system_t::process_new_msg(void) {
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (transceiver.recv(buf, &len)) {
    serial_print("RF - Message: " + String((char *)buf));

    transceiver.send((uint8_t *)NRF24L01_ACK, sizeof((uint8_t *)NRF24L01_ACK));
    serial_print("RF - ACK sent");

    return ((char *)buf);
  }
  else
    serial_print("RF - Failed to retrieve message");

  return ("");
}

/** 
 * @brief Apresenta mensagens do módulo 'System', quando com o modo DEBUG ativado.
 *
 * @param msg Mensagem a ser apresentada no console.
 */
void tractian_system_t::serial_print(String msg) {
  #ifdef SYSTEM_DEBUG_MODE_ON
    Serial.println("[" + String(millis()) + "] " + msg);
  #endif /*SYSTEM_DEBUG_MODE_ON*/
}
