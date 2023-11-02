
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32_Servo.h>
Servo S1;
Servo S2;
const byte diachi[] = "12345";
RF24 radio(4,5); 
int A1 = 13;
int A2 = 12; 
int B2 = 14;
int B3 = 27;
int C1 = 22;
int C2 = 21;
int D1 = 33;
int D2 = 32;
int mode = 0;
int mode2 = 0;
int pos_tay_day = 0;
int pwmA  = 16;
int pwmB  = 17;
int pwmC  = 1;
int pwmD  = 3;
bool isFast = true;
bool isGap = false;
struct Signal {
  byte throttle;      
  byte pitch;
  byte roll;
  byte yaw;
  byte mode;
  byte IO1;
  byte IO2;
  byte isSpeed;
  
};
Signal data;
void in_gia_tri(){
  Serial.print(data.throttle); Serial.print("     ");
  Serial.print(data.pitch); Serial.print("     ");
  Serial.print(data.roll); Serial.print("     ");
  Serial.print(data.yaw); Serial.print("     ");
  Serial.print(data.IO1); Serial.print("     ");
  Serial.print(data.IO2); Serial.print("     ");
  Serial.print(data.isSpeed); Serial.println("     ");
  
}
void setPWM(int speed){
  analogWrite(pwmA,speed);
  Serial.print("speed = ");
  Serial.println(speed);  
}
void A(int direction, int speed){
    if(direction == 1){
      digitalWrite(A1,1);
      digitalWrite(A2,0);
    }else if(direction == 0){
      digitalWrite(A1,0);
      digitalWrite(A2,0);
    }else{
      digitalWrite(A1,0);
      digitalWrite(A2,1);
    }
}
void B(int direction, int speed){
  if(direction == 1){
    digitalWrite(B2,1);
    digitalWrite(B3,0);
  }else if(direction == 0){
    digitalWrite(B2,0);
    digitalWrite(B3,0);
  }else{
    digitalWrite(B2,0);
    digitalWrite(B3,1);
  }
}
void C(int direction, int speed){
  if(direction == 1){
    digitalWrite(C1,1);
    digitalWrite(C2,0);
  }else if(direction == 0){
    digitalWrite(C1,0);
    digitalWrite(C2,0);
  }else{
    digitalWrite(C1,0);
    digitalWrite(C2,1);
  }
}
void D(int direction, int speed){
  
  if(direction == 1){
    digitalWrite(D1,1);
    digitalWrite(D2,0);
  }else if(direction == 0){
    digitalWrite(D1,0);
    digitalWrite(D2,0);
  }else{
    digitalWrite(D1,0);
    digitalWrite(D2,1);
  }
}
void forward(){
  A(1,1);
  B(1,1);
  C(1,1);
  D(1,1);
} 
void backward(){
  A(-1,1);
  B(-1,1);
  C(-1,1);
  D(-1,1);
}
void stop(){
  A(0,1);
  B(0,1);
  C(0,1);
  D(0,1);
}
void spinLeft(){
  A(-1,1);
  B(1,1);
  C(1,1);
  D(-1,1);
}
void spinRight(){
  A(1,1);
  B(-1,1);
  C(-1,1);
  D(1,1);
}
void right(){
  A(1,1);
  B(-1,1);
  C(1,1);
  D(-1,1);
}
void left(){
  A(-1,1);
  B(1,1);
  C(-1,1);
  D(1,1);
}
void setup(){
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(B3,OUTPUT);
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  S1.attach(2);
  S2.attach(15);
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
// pos thả bóng 70;
// pos gắp 255;
// pó thả không 0
// pos thả 1 51
// pos thả 2 120
// pos thả 3 200

void loop(){  
         
        if(radio.available()){
          // thror  pitch roll yaw
            
            radio.read(&data, sizeof(Signal));
            if(data.pitch > 160)forward();
            else if(data.pitch < 80) backward();
            else if(data.roll > 200 ) spinRight();
            else if(data.roll < 50 ) spinLeft();
            else if(data.yaw <= 10) right();
            else if(data.yaw >= 245) left();
            else stop();
              if(data.IO2 == 1){
                delay(200);
                while(data.IO2 == 1) radio.read(&data,sizeof(Signal));
                isGap = !isGap;
              }
              if(data.IO1 == 1){
                delay(200);
                  while(data.IO1 == 1) radio.read(&data, sizeof(Signal));
                  mode++;
                  delay(300);
              }
              if(data.isSpeed == 1) setPWM(255);
              else setPWM(100);
        if(mode % 4 == 0){
          S2.write(0);
        }else if(mode % 4 == 1){
          S2.write(51);
        }else if(mode % 4 == 2){
          S2.write(120);
        }else if(mode % 4 == 3){
          S2.write(200);
        }
        if(isGap) S1.write(180);
        else S1.write(50);
        in_gia_tri();
        }   
        
}
