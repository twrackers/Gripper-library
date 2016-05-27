#include <Servo.h>
#include <Gripper.h>

int closed = 560;   // microseconds
int opened = 1420;  // microseconds
int timeout = 600;  // milliseconds

Gripper gripper(9, closed, opened, timeout);

void setup() 
{
}

void loop() 
{
  if (digitalRead(2) == 0) {
    gripper.open();
  } else if (digitalRead(3) == 0) {
    gripper.close();
  }
  gripper.update();
}
