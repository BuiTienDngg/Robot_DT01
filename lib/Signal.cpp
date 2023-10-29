#include <Arduino.h>
#include <signal.h>
struct Signal {
  byte throttle;      
  byte pitch;
  byte roll;
  byte yaw;
  byte mode;
  byte IO1;
  byte IO2;
};