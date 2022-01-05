#include <NewPing.h>
#include <Wire.h>

const uint8_t TWI_ADDRESS = 0xA1;
const uint8_t ECHO1 = 7;
const uint8_t TRIGGER1 = 8;
const uint8_t ECHO2 = 12;
const uint8_t TRIGGER2 = 13;
const uint8_t MAX_DISTANCE = 100;

uint8_t data[] = {0, 0};

NewPing sonar1(TRIGGER1, ECHO1, MAX_DISTANCE);
NewPing sonar2(TRIGGER2, ECHO2, MAX_DISTANCE);

void twiRequestCallback() {
  Wire.write(data, 2);
  Serial.println("[TWI] - OK - data successfully written");
}

void setup() {
  Serial.begin(115200);
  
  Wire.begin(TWI_ADDRESS);
  Wire.onRequest(twiRequestCallback);
  Serial.println("[TWI] - OK - initialized successfully");
}

void loop() {
  delay(30);
  data[0] = sonar1.ping_cm();
  delay(30);
  data[1] = sonar2.ping_cm();

  Serial.print("[SN1] - OK - value: ");
  Serial.println(data[0]);
  Serial.print("[SN2] - OK - value: ");
  Serial.println(data[1]);
}
