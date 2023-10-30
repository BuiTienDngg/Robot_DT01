#include<Arduino.h>
#include "ControlMotor.h"
#include "Signal.h"
void stop(){
  digitalWrite(A1,0);
  digitalWrite(A2,0);
  digitalWrite(B2,0);
  digitalWrite(B3,0);
  digitalWrite(C1,0);
  digitalWrite(C2,0);
  digitalWrite(D1,0);
  digitalWrite(D2,0);
}
void forWard(){
  digitalWrite(A1,1);
  digitalWrite(A2,0);
  digitalWrite(B2,0);
  digitalWrite(B3,1);
  digitalWrite(C1,0);
  digitalWrite(C2,1);
  digitalWrite(D1,0);
 digitalWrite(D2,1);

}
void backWard(){
  digitalWrite(A1,0);
  digitalWrite(A2,1);
  digitalWrite(B2,1);
  digitalWrite(B3,0);
  digitalWrite(C1,1);
  digitalWrite(C2,0);
  digitalWrite(D1,1);
  digitalWrite(D2,0);

}
void right(){
  digitalWrite(A1,1);
  digitalWrite(A2,0);
  digitalWrite(B2,1);
  digitalWrite(B3,0);
  digitalWrite(C1,0);
  digitalWrite(C2,1);
  digitalWrite(D1,1);
  digitalWrite(D2,0);
}
void left(){
  digitalWrite(A1,0);
  digitalWrite(A2,1);
  digitalWrite(B2,0);
  digitalWrite(B3,1);
  digitalWrite(C1,1);
  digitalWrite(C2,0);
  digitalWrite(D1,0);
  digitalWrite(D2,1);
}
void spinRight(){
  // AD thuận BD nghịch
  digitalWrite(A1,1);
  digitalWrite(A2,0);
  digitalWrite(D1,0);
  digitalWrite(D2,1);

  digitalWrite(B2,1);
  digitalWrite(B3,0);
  digitalWrite(C1,1);
  digitalWrite(C2,0);
} 
void spinLeft(){
  digitalWrite(A1,0);
  digitalWrite(A2,1);
  digitalWrite(D1,1);
  digitalWrite(D2,0);

  digitalWrite(B2,0);
  digitalWrite(B3,1);
  digitalWrite(C1,0);
  digitalWrite(C2,1);
}