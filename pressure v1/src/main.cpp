// #define BLYNK_PRINT Serial
#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Adafruit_ADS1015.h"

//  max adc=32768 
// 1x gain   +/- 4.096V  1 bit =  0.125mV
// 4mA = 1 V /20mA =5V
// vout = V sensor x 0.6
// vsensor = vout / 0.6


#define MAX_TEKANAN_SENSOR 40     //BAR
#define KALIBRASI 4730            //ADC SAAT TEKANAN MINIMUM = 4 mA

#define alamatTekanan1 V0                     //penyimpanan alamat suhu V0-V255
#define alamatTekanan2 V1                     //penyimpanan alamat suhu V0-V255
#define alamatTekanan3 V2                     //penyimpanan alamat suhu V0-V255
#define alamatTekanan4 V3                     //penyimpanan alamat suhu V0-V255
// char auth[] = "OXHw5XoEniLm16AjOSi7qa2AMyvKLW9g";   //masukan token anda
char auth[] = "N58tGgJMm8Rz4XJT2OVQ3fNsQ3uDYQm7"; //anung
char ssid[] = "ardinista";            //nama wifi
char pass[] = "ardiasta";             //password wifi

Adafruit_ADS1115 ads = Adafruit_ADS1115(0x48);
BlynkTimer timer;
BlynkTimer timerWifi;
void event(){
  int16_t adc[4];
  float Tekanan [4];
  for (uint8_t i = 0; i < 4; i++){
    adc[i] = ads.readADC_SingleEnded(i);

    Serial.print("ADC Sensor ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(adc[i]);
    Serial.print("\t\t");

    Serial.print("Tekanan Sensor ");
    Serial.print(i);
    Serial.print(" = ");
    Tekanan[i] = (adc[i] - KALIBRASI ) *(1/480.5);
    Serial.println(Tekanan[i]);
  }
  Serial.println("\n\n");
  Blynk.virtualWrite(alamatTekanan1,Tekanan[0]);
  Blynk.virtualWrite(alamatTekanan2,Tekanan[1]);
  Blynk.virtualWrite(alamatTekanan3,Tekanan[2]);
  Blynk.virtualWrite(alamatTekanan4,Tekanan[3]);
}
void kedip(){
  static uint8_t led;
  if (++led<9){
    digitalWrite(D8,0);
  }
  else{
    digitalWrite(D8,1);
  }
  if(led>20)led=0;
}
void setup(){
  Serial.begin(9600);
  pinMode(D8,OUTPUT);
  digitalWrite(D8,0);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(D0,1);
  timer.setInterval(1000L, event);
  timerWifi.setInterval(100L, kedip);
  ads.begin();
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =  0.125mV
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  timerWifi.run();
}
