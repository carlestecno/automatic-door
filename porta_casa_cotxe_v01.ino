#include "CytronMotorDriver.h"


CytronMD motorD(PWM_DIR, 9,8); //PWM = 9, DIR = 8 (PER DEFECTE)
CytronMD motorE(PWM_DIR, 11, 13);//PWM=11, DIR=13 (PER DEFECTE)

byte lastButtonState;

unsigned long lastTimeButtonStateChanged = millis();
unsigned long debounceDuration = 100; //millis

void obrir_dues(){
  motorD.setSpeed(255);
  delay(4000);
  motorE.setSpeed(255);
  delay(16000);
  motorD.setSpeed(0);
  delay(10000);
  motorE.setSpeed(0);
  delay(99000);
  motorE.setSpeed(-255);
  delay(38000);
  motorD.setSpeed(-255);
  delay(23000);
  
  
}

void obrir_dreta(){
  motorD.setSpeed(255);
  delay(300);
}

void tancar_dreta(){
  motorD.setSpeed(-255);
  delay(300);
}

void obrir_tancar_dreta(){
  motorD.setSpeed(255);
  delay(40000);
  motorD.setSpeed(-255);
  delay(100);
}

void parar(){
  motorD.setSpeed(0);
  motorE.setSpeed(0);
  delay(100);
}
/*
void parar_esquerra(){
  motorE.setSpeed(0);
  delay(100);
}
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
  lastButtonState = digitalRead(7);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available()>0){
    int estat = Serial.read();

    switch(estat){
      case '0':
      obrir_dues();
      break;
      case '1':
      parar();
      break;
      case '3':
      obrir_dreta();
      break;
      case '4':
      tancar_dreta();
      break;
   }    
  }
  if (millis() - lastTimeButtonStateChanged >= debounceDuration){
    byte buttonState = digitalRead(7);
    if (buttonState != lastButtonState){
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (digitalRead(7) == HIGH){
        obrir_tancar_dreta();
        delay(300);
      }
   }
 }
}
