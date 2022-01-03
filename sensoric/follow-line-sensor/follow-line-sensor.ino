#include <Wire.h>

#define TWI_ADDRESS   0xA3
#define OPTRON1       14    // A0
#define OPTRON2       15    // A1
#define OPTRON3       16    // A2

uint8_t color[] = {0, 0, 0};

void twiRequestCallback() {
  Wire.write(color, 3);
  Serial.println("[TWI] - OK - data successfully written");
}

void setup() {
  Serial.begin(9600);
  
  pinMode(OPTRON1, INPUT);
  pinMode(OPTRON2, INPUT);
  pinMode(OPTRON3, INPUT);

  Wire.begin(TWI_ADDRESS);
  Wire.onRequest(twiRequestCallback);
  Serial.println("[TWI] - OK - initialized successfully");
}

void loop() {
    color[0] = analogRead(OPTRON1) / 4;
    Serial.println("[OP1] - OK - value: " + color[0]);
    color[1] = analogRead(OPTRON2) / 4;
    Serial.println("[OP2] - OK - value: " + color[1]);
    color[2] = analogRead(OPTRON3) / 4;
    Serial.println("[OP3] - OK - value: " + color[2]);
    delay(50);
}
