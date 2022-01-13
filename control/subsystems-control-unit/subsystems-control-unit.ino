#include <Protorduino.h>
#include <Wire.h>
#include <SRSC.h>
#include "sensor.h"

const uint8_t frontInterruptPin = 2;
const uint8_t backInterruptPin = 3;

volatile bool frontInterrupted = false;
volatile bool backInterrupted = false;

Protorduino protorduino(5);
SRSC srsc(Serial);

Sensor lidar(0xA0, 3, 20);
Sensor frontSonars(0xA1, 2, 60);
Sensor backSonars(0xA2, 2, 60);
Sensor lineTrackingSensor(0xA3, 4, 50);
//Sensor gps(0xA4, 3, 50);

void frontInterrupt() {
  frontInterrupted = true;

  /*
   * stop motors
   */
}

void backInterrupt() {
  backInterrupted = true;
  
  /*
   * stop motors
   */
}

void requestSensorData(Sensor sensor) {
  uint8_t* dataBuffer = sensor.getData();
  
  Wire.requestFrom(sensor.getTwiAddress(), sensor.getDataBufferSize());

  for (uint8_t i = 0; i < sensor.getDataBufferSize(); i++) {
    if (!Wire.available()) {
      break;
    }
    
    dataBuffer[i] = Wire.read();
  }
}

void bumperTask() {
  if (frontInterrupted) {
    srsc.writePacket(0x60);

    frontInterrupted = false;
  }

  
  if (backInterrupted) {
    srsc.writePacket(0x61);

    backInterrupted = false;
  }
}

void srscLoopTask() {
  srsc.loop();
}

void lidarTask() {
  uint8_t* lidarBuffer = lidar.getData();
  
  requestSensorData(lidar);

  uint8_t lidarData[2] = {
    lidarBuffer[1],
    lidarBuffer[2]
  };

  srsc.writeBinaryPacket(0x62, lidarData);
  srsc.writePacket(0x63, lidarBuffer[0]);
}

void frontSonarsTask() {
  requestSensorData(frontSonars);

  srsc.writeBinaryPacket(0x64, frontSonars.getData());
}

void backSonarsTask() {
  requestSensorData(backSonars);

  srsc.writeBinaryPacket(0x65, backSonars.getData());
}

void lineTrackingSensorTask() {
  requestSensorData(lineTrackingSensor);

  srsc.writeBinaryPacket(0x66, lineTrackingSensor.getData());
}

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Serial.println("[TWI] - OK - initialized successfully");
  
  srsc.begin();
  Serial.println("[SSC] - OK - initialized successfully");

  srsc.definePacketType(0x60, COMMAND, true);
  Serial.println("[SSC] - OK - \"front bumper\" packet defined successfully");
  srsc.definePacketType(0x61, COMMAND, true);
  Serial.println("[SSC] - OK - \"back bumper\" packet defined successfully");
  srsc.definePacketType(0x62, SHORT);
  Serial.println("[SSC] - OK - \"lidar data\" packet defined successfully");
  srsc.definePacketType(0x63, BYTE);
  Serial.println("[SSC] - OK - \"lidar orientation\" packet defined successfully");
  srsc.definePacketType(0x64, SHORT);
  Serial.println("[SSC] - OK - \"front sonars data\" packet defined successfully");
  srsc.definePacketType(0x65, SHORT);
  Serial.println("[SSC] - OK - \"back sonars data\" packet defined successfully");
  srsc.definePacketType(0x66, INT);
  Serial.println("[SSC] - OK - \"line tracking sensor data\" packet defined successfully");
  
  protorduino.registerTask(&bumperTask, 1, 1);
  Serial.println("[PRO] - OK - bumperTask registered successfully");
  protorduino.registerTask(&srscLoopTask, 1, 2);
  Serial.println("[PRO] - OK - srscLoopTask registered successfully");
  protorduino.registerTask(&lidarTask, lidar.getCycleDuration(), 3);
  Serial.println("[PRO] - OK - lidarTask registered successfully");
  protorduino.registerTask(&frontSonarsTask, frontSonars.getCycleDuration(), 4);
  Serial.println("[PRO] - OK - frontSonarsTask registered successfully");
  protorduino.registerTask(&backSonarsTask, backSonars.getCycleDuration(), 5);
  Serial.println("[PRO] - OK - backSonarsTask registered successfully");
  protorduino.registerTask(&lineTrackingSensorTask, lineTrackingSensor.getCycleDuration(), 6);
  Serial.println("[PRO] - OK - lineTrackingSensorTask registered successfully");

  attachInterrupt(digitalPinToInterrupt(frontInterruptPin), frontInterrupt, RISING);
  Serial.println("[INT] - OK - front interrupt registered successfully");
  attachInterrupt(digitalPinToInterrupt(backInterruptPin), backInterrupt, RISING);
  Serial.println("[INT] - OK - back interrupt registered successfully");
}

void loop() {
  protorduino.loop();
}
