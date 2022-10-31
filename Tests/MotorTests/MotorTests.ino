#include <Servo.h>
Servo motor1; 

void setup() {
  // put your setup code here, to run once:
motor1.attach(9);
}

void loop() {

  motor1.write(60);  
  delay(1000);
  motor1.write(90);  
  delay(1000);  
  

}
