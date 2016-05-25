#include <Servo.h>
#include <Gripper.h>

int closed = 560;
int opened = 1420;

Gripper gripper(9, closed, opened, 220);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if (digitalRead(2) == 0) {
    gripper.open();
  } else if (digitalRead(3) == 0) {
    gripper.close();
  }
  if (gripper.update()) {
    Serial.println(gripper.isOpened());
  }
}
