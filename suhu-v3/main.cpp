#include "max6675.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "OXHw5XoEniLm16AjOSi7qa2AMyvKLW9g";   //masukan token anda
char ssid[] = "ardinista";            //nama wifi
char pass[] = "ardiasta";             //password wifi

int thermoDO = D6;
int thermoCS = D7;
int thermoCLK = D5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

BlynkTimer timer;
void myTimerEvent(){
  Blynk.virtualWrite(V0,thermocouple.readCelsius());
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
