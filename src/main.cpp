#include <Arduino.h>
#include <ESP32_Servo.h>
Servo S1;
void setup(){
  S1.attach(16);
  S1.write(0);
}
void loop(){  
         
        for(int i =0 ; i < 180 ; i ++){
          S1.write(i);
          delay(100);
        }
}
