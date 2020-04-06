// #define BLYNK_PRINT Serial
#include <Arduino.h>

#include "max6675.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define alamatSuhu V5                     //penyimpanan alamat suhu V0-V255
char auth[] = "OXHw5XoEniLm16AjOSi7qa2AMyvKLW9g";   //masukan token anda
// char auth[] = "N58tGgJMm8Rz4XJT2OVQ3fNsQ3uDYQm7"; //anung
char ssid[] = "ardinista";            //nama wifi
char pass[] = "ardiasta";             //password wifi

int DO = D5;
int CS = D6;
int CLK = D7;

MAX6675 *Thermocouple = new MAX6675(CLK, CS, DO);

BlynkTimer timer;
BlynkTimer timerWifi;
void event(){
  Blynk.virtualWrite(alamatSuhu,Thermocouple->readCelsius());
}
void kedip(){
  static uint8_t led;
  if (++led<19){
    digitalWrite(D0,0);
  }
  else{
    digitalWrite(D0,1);
  }
  if(led==20)led=0;
}
void setup(){
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  digitalWrite(D0,0);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(D0,1);
  timer.setInterval(1000L, event);
  timerWifi.setInterval(100L, kedip);
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  timerWifi.run();
}
