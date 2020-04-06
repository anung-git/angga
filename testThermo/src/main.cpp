#include <Arduino.h>

#include "max6675.h"
int DO = D5;
int CS = D6;
int CLK = D7;

MAX6675 *Thermocouple = new MAX6675(CLK, CS, DO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println(Thermocouple->readCelsius());
  // Thermocouple->readCelsius()
  delay(1000);
  // put your main code here, to run repeatedly:
}