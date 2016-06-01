#Gripper library
### Libraries used:
####`Servo` (standard Arduino)
####`StateMachine` (mine, located [here](https://github.com/twrackers/StateMachine-library))
This library supports operation of a servo-driven robotic gripper.  The hardware I used in creating this library are:
- Actobotics parallel gripper kit
- Actobotics Hitec HS-485B standard size servo

The gripper kit, when assembled, only moves its rotating parts through about 90 degrees, restricting the servo's usual 180-degree range of rotation.  Therefore this library's constructor requires the closed and opened pulse widths (in microseconds) which will be used by the `Servo` library's `writeMicroseconds()` method.  The values used will differ, not only from one servo to the next, but more importantly with the relative position of the servo shaft and the arm with the toothed hole.  Values should be used which set the desired range of motion without trying to drive the gripper jaws past their physical limits.

Because a gripper is designed to grip something, this implies that the jaws won't be able to reach the fully-closed position if there's something between them.  This causes a stall condition on the servo motor, which increases the servo's current draw... and makes an unpleasant buzzing sound.  I can think of three ways around this problem, in order of increasing simplicity.
  1. Use a current sensor in series with the servo's supply pin (high-rail sensor) or ground pin (low-rail sensor) to detect the stall, then de-energize the servo.  Because the motor-to-jaw linkage is geared down, the gripper will hold that position as long as you don't pull the jaws apart by hand.
  2. Put a thin force sensor on the gripping surface of one jaw and sense physical contact directly, then de-energize the servo.
  3. Determine how long the jaws take to go from fully open to fully closed, then use that as a timeout to de-energize the servo after it has been commanded to close (or open).

I chose option 3 because it required no additional hardware.  To support this, the library constructor also requires this timeout value, in milliseconds.
