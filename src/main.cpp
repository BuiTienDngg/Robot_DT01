#include <Arduino.h>
#include "C:\Users\admin\Documents\PlatformIO\Projects\rx_robot\lib\ControlMotor.h"
// #include "C:\Users\admin\Documents\PlatformIO\Projects\rx_robot\lib\Signal.h"
// #include "C:\Users\admin\Documents\PlatformIO\Projects\rx_robot\lib\GetPID.h"
// #include <WiFi.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int const s1 = 21;
int const s2 = 22;

const byte diachi[] = "12345";
RF24 radio(4,5); 
struct Signal {
  byte throttle;      
  byte pitch;
  byte roll;
  byte yaw;
  byte mode;
  byte IO1;
  byte IO2;
};
Signal data;
void in_gia_tri();
void setup(){
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(B3,OUTPUT);
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(34,INPUT);
  pinMode(35,INPUT);
  pinMode(36,INPUT);
  pinMode(39,INPUT);
  pinMode(17,INPUT);
  Serial.begin(115200);
  if (!radio.begin()) {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }
  radio.openReadingPipe(1,diachi);
  if (!radio.available()){
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
  radio.startListening(); 
}
void loop(){
        // Blynk.run();
        radio.read(&data, sizeof(Signal));
        if(data.pitch > 200 && data.roll > 100 && data.roll < 180 ) forWard();
        else if(data.pitch < 80 && data.roll > 100 && data.roll < 180) backWard();
        else if(data.roll > 200 && data.pitch > 100 && data.pitch < 180) left();
        else if(data.roll < 50 && data.pitch > 100 && data.pitch < 180) right();
        else if(data.yaw < 10) spinLeft();
        else if(data.yaw > 230) spinRight();
        else stop();
        // in_gia_tri();
        if(data.IO1 == 1){ // nút nhấn thứ 1
            delay(1300);
            radio.read(&data, sizeof(Signal));
            spinLeft();
            delay(800);
            Serial.println("hihi");          
        }
        if(data.IO2 == 1){ // nút nhấn thứ 2
            delay(1300);
            radio.read(&data, sizeof(Signal));
            spinRight();
            delay(800);
            Serial.println("hihi");
            
        }
}

// void sendEncoder(){
//   radio.stopListening();// ngưng nhận để gửi encoder
//   radio.write(&encoder, sizeof(encoder));
//   delay(10);
// }
// void reset(){
//   mode ++;
//   encoder = 0;
//   delay(1000);
// }
// void resetData() {
//   data.throttle = 0;
//   data.yaw = 127;
//   data.pitch = 127;
//   data.roll = 127;
  
// }
void in_gia_tri(){
  Serial.print(data.throttle); Serial.print("     ");
  Serial.print(data.pitch); Serial.print("     ");
  Serial.print(data.roll); Serial.print("     ");
  Serial.print(data.yaw); Serial.print("     ");
  Serial.print(data.IO1); Serial.print("     ");
  Serial.print(data.IO2); Serial.println("     ");
  
}
