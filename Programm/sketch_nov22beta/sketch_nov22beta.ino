// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>


Adafruit_MPU6050 mpu;

  Servo myservo;
  Servo myservo2;
  // create servo object to control a servo
  // twelve servo objects can be created on most boards

  int pos = 0;
  int pos2 = 0;

void setup(void) {

  myservo.attach(9);
  myservo2.attach(6);

}

void loop() {
  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  pos = map((a.acceleration.x)*1000,-10000,10000,0,180);
  myservo.write(pos);
  pos2 = map((a.acceleration.y)*1000,-10000,10000,0,180);
  myservo2.write(pos2);
}
