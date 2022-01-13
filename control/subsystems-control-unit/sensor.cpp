#include "sensor.h"

Sensor::Sensor(uint8_t twiAddress, uint8_t dataBufferSize, uint32_t cycleDuration) : twiAddress(twiAddress), dataBufferSize(dataBufferSize), cycleDuration(cycleDuration), data(new uint8_t[dataBufferSize]) {}

Sensor::Sensor(uint8_t dataBufferSize, uint32_t cycleDuration) : twiAddress(0x0), dataBufferSize(dataBufferSize), cycleDuration(cycleDuration), data(new uint8_t[dataBufferSize]) {}

Sensor::Sensor(uint32_t cycleDuration) : twiAddress(0x0), dataBufferSize(0), cycleDuration(cycleDuration), data(new uint8_t[0]) {}

uint8_t Sensor::getTwiAddress() {
  return twiAddress;
}

uint8_t Sensor::getDataBufferSize() {
  return dataBufferSize;
}

uint8_t* Sensor::getData() {
  return data;
}

uint32_t Sensor::getCycleDuration() {
  return cycleDuration;
}
