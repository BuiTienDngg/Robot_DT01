#include<Arduino.h>
#include "GetPID.h"

BLYNK_WRITE(V4)
{
  // Set incoming value from pin V0 to a variable
  int P = param.asDouble();
  Serial.print("P = "); Serial.println(P);
}
BLYNK_WRITE(V5)
{
  // Set incoming value from pin V0 to a variable
  int I = param.asDouble();
  Serial.print("I = "); Serial.println(I);
}
BLYNK_WRITE(V6)
{
  // Set incoming value from pin V0 to a variable
  int D = param.asDouble();
  Serial.print("D = "); Serial.println(D);
}
BLYNK_WRITE(V7){
    int speed = param.asInt();
    Serial.print("Speed = "); Serial.println(speed);
}