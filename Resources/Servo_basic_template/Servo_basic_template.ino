#include <Servo.h>

Servo servo_01;

void setup()
{
  // put your setup code here, to run once:
  
  servo_01.attach(6);
  servo_01.write(90);  // set servo to mid-point
}

void loop() {
  // put your main code here, to run repeatedly:

}
