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

#include "FabricaDigital_MCP23008.h"

FabricaDigital_MCP23008::FabricaDigital_MCP23008(uint8_t i2cDir) {
  // Establecer dirección i2c
  this->m_i2cDir = i2cDir;

  return;
}

void FabricaDigital_MCP23008::begin() {
  Wire.begin();

  // Opciones por defecto
  Wire.beginTransmission(this->m_i2cDir);

  #if ARDUINO >= 100
    Wire.write((byte) this->MCP23008_IODIR);
    Wire.write((byte) 0xFF);  // todos los pines como entrada
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
    Wire.write((byte) 0x00);
  #else
    Wire.send(this->MCP23008_IODIR);
    Wire.send(0xFF);  // todos los pines como entrada
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
    Wire.send(0x00);
  #endif

  Wire.endTransmission();
}

void FabricaDigital_MCP23008::pinMode(uint8_t pin, uint8_t modo) {
  uint8_t modoPines;

  // Los pines existen de 0 a 7
  if (pin > 7) {
    return;
  }

  // Leer el modo de los pines actual
  modoPines = this->obtenerReg8(this->MCP23008_IODIR);

  // Cambiar la dirección del pin
  if (modo == INPUT) {
    modoPines |= 1 << pin;
  } else {
    modoPines &= ~(1 << pin);
  }

  // Guardar el nuevo modo
  this->establecerReg8(MCP23008_IODIR, modoPines);

  return;
}

void FabricaDigital_MCP23008::digitalWrite(uint8_t pin, uint8_t estado) {
  uint8_t estadoPines;

  // Los pines existen de 0 a 7
  if (pin > 7) {
    return;
  }

  // Leer el estado de los pines actual
  estadoPines = this->obtenerReg8(this->MCP23008_GPIO);

  // Escribe el nuevo estado del pin
  if (estado == HIGH) {
    estadoPines |= 1 << pin;
  } else {
    estadoPines &= ~(1 << pin);
  }

  // Guarda el nuevo estado de los pines
  this->establecerReg8(this->MCP23008_GPIO, estadoPines);

  return;
}

uint8_t FabricaDigital_MCP23008::digitalRead(uint8_t pin) {
  // Los pines existen de 0 a 7
  if (pin > 7) {
    return 0;
  }

  // Devuelve el estado del pin
  return (this->obtenerReg8(this->MCP23008_GPIO) >> pin) & 0x01;
}

void FabricaDigital_MCP23008::digitalWrite(uint8_t estado) {
  establecerReg8(this->MCP23008_GPIO, estado);
}

uint8_t FabricaDigital_MCP23008::digitalRead() {
  return obtenerReg8(this->MCP23008_GPIO);
}

void FabricaDigital_MCP23008::establecerReg8(uint8_t registro, uint8_t dato) {
  Wire.beginTransmission(this->m_i2cDir);

  #if ARDUINO >= 100
    Wire.write((byte) registro);
    Wire.write((byte) dato);
  #else
    Wire.send(addr);
    Wire.send(data);
  #endif

  Wire.endTransmission();

  return;
}

uint8_t FabricaDigital_MCP23008::obtenerReg8(uint8_t registro) {
  Wire.beginTransmission(this->m_i2cDir);

  #if ARDUINO >= 100
    Wire.write((byte) registro);
  #else
    Wire.send(registro);
  #endif

  Wire.endTransmission();
  Wire.requestFrom(this->m_i2cDir, 1u);

  #if ARDUINO >= 100
    return Wire.read();
  #else
    return Wire.receive();
  #endif
}
