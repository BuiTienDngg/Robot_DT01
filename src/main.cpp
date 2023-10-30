#include <Arduino.h>
#include "ControlMotor.h"
// #include "GetPID.h"
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
int sensor[5];
int P = 0, I = 0, D = 0, PID_value = 0;
double Kp = 0.0 , Ki = 0.0, Kd = 0.0;
int Error = 0, previousError = 0;
int initial_motor_speed =200;
TaskHandle_t Task1;
TaskHandle_t Task2;
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
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
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
  xTaskCreatePinnedToCore(
             Task1code, /* Task function. */
             "Task1",   /* name of task. */
             10000,     /* Stack size of task */
             NULL,      /* parameter of the task */
             1,         /* priority of the task */
             &Task1,    /* Task handle to keep track of created task */
             0);        /* pin task to core 0 */   
  delay(500);
  xTaskCreatePinnedToCore(
             Task2code,  /* Task function. */
             "Task2",    /* name of task. */
             10000,      /* Stack size of task */
             NULL,       /* parameter of the task */
             1,          /* priority of the task */
             &Task2,     /* Task handle to keep track of created task */
             1);         /* pin task to core 0 */   
  delay(500);
}
void Task1code( void * pvParameters ){ // do line
  sensor[0]=digitalRead(S0);
  sensor[1]=digitalRead(S1);
  sensor[2]=digitalRead(S2);
  sensor[3]=digitalRead(S3);
  sensor[4]=digitalRead(S4);
  
  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==1))
  Error=4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==1))
  Error=3;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==0))
  Error=2;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==1)&&(sensor[4]==0))
  Error=1;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
  Error=0;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
  Error=-1;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  Error=-2;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  Error=-3;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  Error=-4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
    if(Error==-4) Error=-5;
    else Error=5;
}
void Task2code( void * pvParameters ){ // calculator
    P = Error;
    I = I + Error;
    D = Error - previousError;
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    previousError=Error;
    int left_motor_speed = initial_motor_speed-PID_value;
    int right_motor_speed = initial_motor_speed+PID_value;
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
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
void in_gia_tri(){
  Serial.print(data.throttle); Serial.print("     ");
  Serial.print(data.pitch); Serial.print("     ");
  Serial.print(data.roll); Serial.print("     ");
  Serial.print(data.yaw); Serial.print("     ");
  Serial.print(data.IO1); Serial.print("     ");
  Serial.print(data.IO2); Serial.println("     ");
  
}
