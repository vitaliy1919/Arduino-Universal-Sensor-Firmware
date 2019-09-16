#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "SparkfunADXL335.h"
#include "IvensenseITG3200.h"
#include <ITG3200.h>
const int kSensorNumber = 2;
// _ITG3200 gyro(0x69);
IvensenseITG3200_Unified itg3200(1, 0x69);
Adafruit_Sensor *sensor[] = {
  // new Spartkfun_ADXL345_Unified(0, A0, A1, A2),
  new IvensenseITG3200_Unified::Temperature(&itg3200),
  new IvensenseITG3200_Unified::Gyro(&itg3200)

};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // sensor[0]->begin();
  for (int i = 0; i < kSensorNumber; i++) {
    sensor[i]->begin();
    // Serial.println(i);
  }
}

void loop() {
  sensors_event_t event;
  // sensor[0]->getEvent(&event);
  // writeEvent(&event);

  for (int i = 0; i < kSensorNumber; i++) 
  {
    sensor[i]->getEvent(&event);
    writeEvent(&event);
    Serial.println();
  }

  // put your main code here, to run repeatedly:
}