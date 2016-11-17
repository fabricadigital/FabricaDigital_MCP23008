/**
 * Librería MCP23008 para Arduino
 * Copyright 2016 - Fábrica Digital (fabricadigital.org)
 *
 * Publicado bajo licencia CC-BY-SA 4.0
 * Creative Commons: Reconocimiento - Compartir Igual 4.0 Internacional
 * http://creativecommons.org/licenses/by-sa/4.0/deed.es_ES
 *
 * Modificado el 4 de febrero de 2016
 * por Pablo Bacho para Fábrica Digital
 */

#ifndef _FABRICADIGITAL_MCP23008_H_
#define _FABRICADIGITAL_MCP23008_H_

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
  #include <TinyWireM.h>
  #define Wire TinyWireM
#else
  #include <Wire.h>
#endif

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

class FabricaDigital_MCP23008 {
public:
  FabricaDigital_MCP23008();
  FabricaDigital_MCP23008(uint8_t i2cDir);
  void begin(uint8_t direccionI2C);
  void begin();
  void pinMode(uint8_t pin, uint8_t modo);
  void digitalWrite(uint8_t pin, uint8_t estado);
  uint8_t digitalRead(uint8_t pin);
  void pullUp(uint8_t pin, uint8_t pullUp);
  void digitalWrite(uint8_t estado);
  uint8_t digitalRead();
  void pullUp(uint8_t pullUp);

private:
  uint8_t m_i2cDir;

  // Registros
  static const uint8_t MCP23008_IODIR = 0x00;
  static const uint8_t MCP23008_IPOL = 0x01;
  static const uint8_t MCP23008_GPINTEN = 0x02;
  static const uint8_t MCP23008_DEFVAL = 0x03;
  static const uint8_t MCP23008_INTCON = 0x04;
  static const uint8_t MCP23008_IOCON = 0x05;
  static const uint8_t MCP23008_GPPU = 0x06;
  static const uint8_t MCP23008_INTF = 0x07;
  static const uint8_t MCP23008_INTCAP = 0x08;
  static const uint8_t MCP23008_GPIO = 0x09;
  static const uint8_t MCP23008_OLAT = 0x0A;

  void establecerReg8(uint8_t registro, uint8_t dato);
  uint8_t obtenerReg8(uint8_t registro);
};

#endif
