#include <Protorduino.h>
#include <TFMPlus.h>
#include <StepperMotor.h>
#include <Wire.h>

#define TWI_ADDRESS   0xA0
#define STEPPER1      8
#define STEPPER2      9
#define STEPPER3      10
#define STEPPER4      11

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
uint8_t movesPerMeasurement = 10 / (8 * stepDelay);
uint8_t additionalMeasurementDelay = 10 % (8 * stepDelay);

void twiRequestCallback() {
  Wire.write(data, 3);
}

void measurementTask() {
  readSuccess = lidar.getData(distance, flux, temperature);
  
  if (readSuccess && flux > 1000) {
    data[0] = motorSteps;
    data[1] = distance & 0xff;
    data[2] = (distance >> 8) & 0xff;
  }
}

void movementTask() {
  if (motorDirection) {
    motorSteps++;
    stepper.moveForward();
    motorDirection = motorSteps < 127;
  } else {
    motorSteps--;
    stepper.moveBackwards();
    motorDirection = motorSteps > 0;
  }
}

void setup() {
  Serial.begin(115200);

  protorduino.registerTask(&measurementTask, 10, 1);
  protorduino.registerTask(&movementTask, 8, 2);
  
  Wire.begin(TWI_ADDRESS);
  Wire.onRequest(twiRequestCallback);
  
  lidar.begin(&Serial);                                     // lidar starts with default values (baud-rate = 115200 Bd and frame-rate = 100 Hz)
}

void loop() {
  protorduino.execute();
}
