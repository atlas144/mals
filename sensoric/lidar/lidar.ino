#include <Protorduino.h>
#include <TFMPlus.h>
#include <StepperMotor.h>
#include <Wire.h>

const uint8_t TWI_ADDRESS = 0xA0;
const uint8_t STEPPER1 = 8;
const uint8_t STEPPER2 = 9;
const uint8_t STEPPER3 = 10;
const uint8_t STEPPER4 = 11;

uint8_t stepDelay = 1;

Protorduino protorduino(2);
TFMPlus lidar;
StepperMotor stepper(STEPPER1, STEPPER2, STEPPER3, STEPPER4, stepDelay);

uint8_t data[] = {0, 0, 0};                                 // {motorSteps, distance (byte 0), distance (byte 1)}

int16_t distance = 0;
int16_t flux = 0;
int16_t temperature = 0;

bool readSuccess = false;

uint8_t motorSteps = 0;
bool motorDirection = true;  // 1 - forward, 0 - backwards

void twiRequestCallback() {
  Wire.write(data, 3);
  Serial.println("[TWI] - OK - data successfully written");
}

void measurementTask() {
  readSuccess = lidar.getData(distance, flux, temperature);
  
  if (readSuccess && flux > 1000) {
    data[0] = motorSteps;
    data[1] = distance & 0xff;
    data[2] = (distance >> 8) & 0xff;
    
    Serial.print("[LID] - OK - measurement successfull (");
    Serial.print(distance);
    Serial.println(")");
  } else {
    Serial.println("[LID] - ERR - measurement unsuccessfull");
  }
}

void movementTask() {
  if (motorDirection) {
    motorSteps++;
    stepper.moveForward();
    motorDirection = motorSteps < 127;
    Serial.println("[STP] - OK - moved forward");
  } else {
    motorSteps--;
    stepper.moveBackwards();
    motorDirection = motorSteps > 0;
    Serial.println("[STP] - OK - moved backwards");
  }
}

void setup() {
  Serial.begin(115200);

  protorduino.registerTask(&measurementTask, 10, 1);
  Serial.println("[PRO] - OK - measurementTask registered successfully");
  protorduino.registerTask(&movementTask, 8, 2);
  Serial.println("[PRO] - OK - movementTask registered successfully");
  
  Wire.begin(TWI_ADDRESS);
  Wire.onRequest(twiRequestCallback);
  Serial.println("[TWI] - OK - initialized successfully");
  
  lidar.begin(&Serial);                                     // lidar starts with default values (baud-rate = 115200 Bd and frame-rate = 100 Hz)
  Serial.println("[LID] - OK - initialized successfully");
}

void loop() {
  protorduino.execute();
}
