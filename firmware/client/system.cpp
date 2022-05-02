/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        system.cpp                                   Author  : Rafael Feijó Leonardo        */
/*                                                     Email   : goldcard99@hotmail.com       */
/*                                                     Address : DF, BRAZIL, 70670-403        */
/*        Created: 2022/04/30 21:32:04 by rFeijo                                              */
/*        Updated: 2022/05/01 15:34:54 by rFeijo                                              */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include "system.h"

RH_NRF24 transceiver(2, 4);

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
 * @brief Inicializa a memória flash do uC.
 */
bool tractian_system_t::mount_spiffs(void) {
  if (!LittleFS.begin())
    return (false);

  return (true);
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
 *  @brief Envia uma mesagem para a rede RF criada.
 */
void tractian_system_t::send_message(void) {
  File fp = LittleFS.open(SPIFFS_FILE_NAME, SPIFFS_OP_MODE);

  if (!fp) {
    serial_print("SPIFFS - Failed to open file");
    
    return;
  }

  uint8_t msg[RH_NRF24_MAX_MESSAGE_LEN], index = 0;
  while (fp.available()) {
    msg[index++] = (uint8_t)fp.read();

    if (index == (RH_NRF24_MAX_MESSAGE_LEN - 1)) {
      msg[index] = (uint8_t)'\0';

      serial_print("Message size: " + String(get_sizeof_msg(msg)));
      serial_print((char *)msg);
      
      transceiver.send(msg, get_sizeof_msg(msg));
      transceiver.waitPacketSent();
      
      index = 0;
    }
  }

  if (index > 0) {
    msg[index] = (uint8_t)'\0';
    
    transceiver.send(msg, get_sizeof_msg(msg));
    transceiver.waitPacketSent();
  }

  fp.close();

  wait_for_ack();
}

/* 
 *  @brief Espera um retorno (ack) do servidor.
 */
void tractian_system_t::wait_for_ack(void) {
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (transceiver.waitAvailableTimeout(NRF24L01_DELAY)) {
    if (transceiver.recv(buf, &len)) {
      serial_print("RF - New message received");
      serial_print("RF - Message: " + String((char *)buf));
    }
    else
      serial_print("RF - Failed to retrieve message");
  }
  else
    serial_print("RF - Failed to sync with server (is it running?)");
}

uint8_t tractian_system_t::get_sizeof_msg(uint8_t *ptr) {
  uint8_t length = 1;

  if (!ptr)
    return (0);

  while (ptr[length] != '\0')
    length++;

  return (length);
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
