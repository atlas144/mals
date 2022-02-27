#include <Protorduino.h>
#include <Wire.h>
#include <SRSC.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "sensor.h"
#include "serializableFloat.h"

const uint8_t frontInterruptPin = 2, backInterruptPin = 3, ssRx = 12, ssTx = 13;

volatile bool frontInterrupted = false;
volatile bool backInterrupted = false;

SerializableFloat lat, lon;
unsigned long age;

Protorduino protorduino(5);
SRSC srsc(Serial);
SoftwareSerial ss(ssRx, ssTx);
TinyGPS gps;

Sensor lidar(0xA0, 3, 20);
Sensor frontSonars(0xA1, 2, 60);
Sensor backSonars(0xA2, 2, 60);
Sensor lineTrackingSensor(0xA3, 4, 50);
Sensor gpsInterface(50);

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

void readPacketTask() {
  while (srsc.isAvailable()) {
    Packet *packet;
    
    if (srsc.readPacket(packet)) {
      Serial.print(F("[SSC] - OK - packet:"));
      Serial.println(packet->getPayload());
      
      /*switch (packet->getPacketType()) {
        case 0x60: {
          
        }
      }*/
    } else {
      Serial.println(F("[SSC] - ERR - packet reading failed"));
    }
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

void gpsTask() {
  bool newData = false;
  
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      newData = true;
    }
  }

  if (newData) {
    gps.f_get_position(&lat.number, &lon.number, &age);
    srsc.writeBinaryPacket(0x67, lat.bynary);
    srsc.writeBinaryPacket(0x68, lon.bynary);
  }
}

void setup() {
  Serial.begin(115200);
  
  ss.begin(4800);
  Serial.println(F("[SWS] - OK - initialized successfully"));
  
  Wire.begin();
  Serial.println(F("[TWI] - OK - initialized successfully"));
  
  srsc.begin();
  Serial.println(F("[SSC] - OK - initialized successfully"));

  // Motor packets
  for (uint8_t i = 0; i < 4; i++) {
    srsc.definePacketType(0x60 + i * 3, COMMAND, true);
    srsc.definePacketType(0x61 + i * 3, COMMAND, true);
    srsc.definePacketType(0x62 + i * 3, BYTE);
  }

  // Lidar packets
  srsc.definePacketType(0x72, SHORT);
  srsc.definePacketType(0x73, BYTE);
  
  // Sonars packets
  for (uint8_t i = 0; i < 2; i++) {
    srsc.definePacketType(0x74 + i, SHORT);
  }

  // Line tracking sensor packet
  srsc.definePacketType(0x76, INT);

  // Bumpers packets
  for (uint8_t i = 0; i < 2; i++) {
    srsc.definePacketType(0x77 + i, COMMAND, true);
  }

  // GPS packets
  for (uint8_t i = 0; i < 2; i++) {
    srsc.definePacketType(0x79 + i, INT);
  }
  
  Serial.println(F("[SSC] - OK - packet types registered successfully"));
  
  protorduino.registerTask(&bumperTask, 1, 1);
  Serial.println(F("[PRO] - OK - bumperTask registered successfully"));
  protorduino.registerTask(&srscLoopTask, 1, 2);
  Serial.println(F("[PRO] - OK - srscLoopTask registered successfully"));
  protorduino.registerTask(&readPacketTask, 20, 3);
  Serial.println(F("[PRO] - OK - readPacketTask registered successfully"));
  protorduino.registerTask(&lidarTask, lidar.getCycleDuration(), 4);
  Serial.println(F("[PRO] - OK - lidarTask registered successfully"));
  protorduino.registerTask(&frontSonarsTask, frontSonars.getCycleDuration(), 5);
  Serial.println(F("[PRO] - OK - frontSonarsTask registered successfully"));
  protorduino.registerTask(&backSonarsTask, backSonars.getCycleDuration(), 6);
  Serial.println(F("[PRO] - OK - backSonarsTask registered successfully"));
  protorduino.registerTask(&lineTrackingSensorTask, lineTrackingSensor.getCycleDuration(), 7);
  Serial.println(F("[PRO] - OK - lineTrackingSensorTask registered successfully"));
  protorduino.registerTask(&gpsTask, gpsInterface.getCycleDuration(), 8);
  Serial.println(F("[PRO] - OK - gpsTask registered successfully"));

  attachInterrupt(digitalPinToInterrupt(frontInterruptPin), frontInterrupt, RISING);
  Serial.println(F("[INT] - OK - front interrupt registered successfully"));
  attachInterrupt(digitalPinToInterrupt(backInterruptPin), backInterrupt, RISING);
  Serial.println(F("[INT] - OK - back interrupt registered successfully"));
}

void loop() {
  protorduino.loop();
}
