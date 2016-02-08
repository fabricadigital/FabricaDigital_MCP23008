/**
 * Blink_MCP23008
 * Parpadea un led en el pin 5 del MCP23008.
 *
 * Este ejemplo es de dominio público.
 *
 * Modificado el 4 de febrero de 2016
 * por Pablo Bacho para Fábrica Digital
 */

#include <Wire.h>
#include "FabricaDigital_MCP23008.h"

const int LED_PIN = 5; // Pin del MCP23008 en el que se conecta el LED

const int MCP23008_I2C_DIR = 0x20; // Dirección I2C del MCP23008
FabricaDigital_MCP23008 pinesExtra(MCP23008_I2C_DIR);

void setup() {
  pinesExtra.begin();
  pinesExtra.pinMode(LED_PIN, OUTPUT);
}

void loop() {
  pinesExtra.digitalWrite(LED_PIN, HIGH);
  delay(500);
  pinesExtra.digitalWrite(LED_PIN, LOW);
  delay(500);
}
