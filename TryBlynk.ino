#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 0

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "p4UzwkPN_JGzmWihu_wehTvRO956xqGQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wi-Fi";
char pass[] = "t4np4k4bel";
const int pinLDR = 36;
const int pinDHT = 4;
const int ledMerahDHT = 25;
const int ledHijauDHT = 33;
const int ledMerahLDR = 26;
const int ledHijauLDR = 32;


WidgetLED greenLEDLDR(V0);
WidgetLED redLEDLDR(V1);
WidgetLED greenLEDDHT(V2);
WidgetLED redLEDDHT(V3);
//const float nilai = 0,009768;

DHT dht(pinDHT, DHTTYPE);
BlynkTimer timer;
int setpointDHT = 0;
int setpointLDR = 0;
int nyala = 0;

void sendSensor(){
  //DHT11
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, t);
  if(t>setpointDHT){
    redLEDDHT.on();
    greenLEDDHT.off();
  }
  else {
    redLEDDHT.off();
    greenLEDDHT.on();
  }
   
  //LDR
  float ldr = analogRead(pinLDR);
  ldr = 0.009768*ldr+10;
  if (isnan(ldr)) {
    Serial.println("Failed to read from Brighthness sensor!");
    return;
  }
  Blynk.virtualWrite(V6, ldr);
  if(ldr>setpointLDR){
    redLEDLDR.on();
    greenLEDLDR.off();
  }
  else {
    redLEDLDR.off();
    greenLEDLDR.on();
  }
  Serial.println(setpointDHT);
  Serial.println(setpointLDR);
}


BLYNK_WRITE(V11){
  setpointDHT = param.asInt();
}
BLYNK_WRITE(V10){
  setpointLDR = param.asInt();
}
BLYNK_WRITE(V7){
  nyala = param.asInt();
}
void setup(){
  
  delay(5000);
  Serial.begin(9600);
  pinMode(pinLDR, INPUT);
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,100,84), 8080);
  Serial.println(F("Sensor Begin !"));

  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop(){
  float t = dht.readTemperature();
  float ldr = analogRead(pinLDR);
  ldr = 0.009768*ldr+10;
  delay(1000);
  Blynk.run();
  
  if(nyala == 1){
    sendSensor();
    timer.run();
  }
  
  
  //ldr = ldr*nilai+10;
  Serial.print(t, 0);
  Serial.print(F("°C "));
  Serial.println(ldr, 0);
  
  //jika DHT gagal membaca suhu
  if (isnan(t)) {
    Serial.println(F("Gagal membaca suhu !"));
    return;
  }
  
  //DHT11
//  if(t>=setpointDHT){
//    digitalWrite(ledMerahDHT, HIGH);
//    digitalWrite(ledHijauDHT, LOW);
//  }
//  else{
//    digitalWrite(ledHijauDHT, HIGH);
//    digitalWrite(ledMerahDHT, LOW); 
//  }

  //LDR
//  if(ldr >= setpointLDR){
//    digitalWrite(ledMerahLDR, HIGH);
//    digitalWrite(ledHijauLDR, LOW);
//  }
//  else{
//    digitalWrite(ledHijauLDR, HIGH);
//    digitalWrite(ledMerahLDR, LOW); 
//  }
  
}
