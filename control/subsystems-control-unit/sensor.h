#ifndef SENSOR_H
#define SENSOR_H

#include <SRSC.h>

class Sensor {
  private:
    uint8_t twiAddress;
    uint8_t dataBufferSize;
    uint8_t* data;
    uint32_t cycleDuration;
  public:
    Sensor(uint8_t twiAddress, uint8_t dataBufferSize, uint32_t cycleDuration);
    Sensor(uint8_t dataBufferSize, uint32_t cycleDuration);
    Sensor(uint32_t cycleDuration);
    uint8_t getTwiAddress();
    uint8_t getDataBufferSize();
    uint8_t* getData();
    uint32_t getCycleDuration();
};

#endif
