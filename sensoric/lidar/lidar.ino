#include <Protorduino.h>
#include <SoftwareSerial.h>   
#include <TFMPlus.h>
#include <Servo.h>
#include <Wire.h>

const uint8_t TWI_ADDRESS = 0x22;
const uint8_t SERVO = 9;

Protorduino protorduino(2);
SoftwareSerial swSerial(10, 11); 
TFMPlus lidar;
Servo servo;

uint8_t data[] = {0, 0, 0};                                 // {angle, distance (byte 0), distance (byte 1)}

int16_t distance = 0;
int16_t flux = 0;
int16_t temperature = 0;

bool readSuccess = false;

uint8_t angle = 90;
bool motorDirection = true;  // 1 - forward, 0 - backwards

void twiRequestCallback() {
  Wire.write(data, 3);
  swSerial.println(F("[TWI] - OK - data successfully written"));
}

void measurementTask() {
  readSuccess = lidar.getData(distance, flux, temperature);
  
  if (readSuccess && flux > 1000) {
    data[0] = angle;
    data[1] = distance & 0xff;
    data[2] = (distance >> 8) & 0xff;
    
    swSerial.print(F("[LID] - OK - measurement successfull ("));
    swSerial.print(distance);
    swSerial.println(F(")"));
  } else {
    swSerial.println(F("[LID] - ERR - measurement unsuccessfull"));
  }
}

void movementTask() {
  if (motorDirection) {
    angle++;
    servo.write(angle);
    motorDirection = angle < 150;
    swSerial.print(F("[STP] - OK - moved forward (angle "));
    swSerial.print(angle);
    swSerial.println(F(")"));
  } else {
    angle--;
    servo.write(angle);
    motorDirection = angle < 90;
    swSerial.print(F("[STP] - OK - moved backwards (angle "));
    swSerial.print(angle);
    swSerial.println(F(")"));
  }
}

void setup() {
  Serial.begin(115200);
  swSerial.begin(115200);

  protorduino.registerTask(&measurementTask, 10, 1);
  swSerial.println(F("[PRO] - OK - measurementTask registered successfully"));
  protorduino.registerTask(&movementTask, 8, 2);
  swSerial.println(F("[PRO] - OK - movementTask registered successfully"));
  
  Wire.begin(TWI_ADDRESS);
  Wire.onRequest(twiRequestCallback);
  swSerial.println(F("[TWI] - OK - initialized successfully"));
  
  lidar.begin(&Serial);                                     // lidar starts with default values (baud-rate = 115200 Bd and frame-rate = 100 Hz)
  swSerial.println(F("[LID] - OK - initialized successfully"));
}

void loop() {
  protorduino.loop();
}
