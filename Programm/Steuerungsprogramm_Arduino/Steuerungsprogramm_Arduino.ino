// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>
#include <EEPROM.h>

Adafruit_MPU6050 mpu;

Servo myservo;
Servo myservo2;

int pos = 0;
int pos2 = 0;

//SETTINGS
float filterfaktor = 0.1;
int gyroswitch = 2;
int xoffset = 0;
int yoffset = 0;

bool gyroswitchflag = false;

float xvals[3];
float yvals[3];
float diffacc = 0;

double cycletime;


void setup(void) {

  Serial.begin(9600);

  myservo.attach(9);
  myservo2.attach(6);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

}

void loop() {
  cycletime = millis();

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (!gyroswitchflag) {
    xvals[1] = accx_filtered(a.acceleration.x);
    yvals[1] = accy_filtered(a.acceleration.y);
  }

  if (((xvals[1] * yvals[1]) - (diffacc * diffacc)) > gyroswitch ^ 2) {
    gyroswitchflag = true;

    xvals[1] += (g.gyro.x) / ((millis() - cycletime) / 1000);
    yvals[1] += (g.gyro.y) / ((millis() - cycletime) / 1000);

  } else {
    gyroswitchflag = false;
  }

  setservos(xvals[1] + xoffset, yvals[1] + yoffset);

  diffacc = xvals[1] * yvals[1];
}


void setservos(int accx, int accy) {
  pos = map((accx) * 1000, -10000, 10000, 1000, 2000);
  myservo. writeMicroseconds(pos);
  pos2 = map((accy) * 1000, -10000, 10000, 1000, 2000);
  myservo2.write(pos2);
}

float accx_filtered(float accx) {
  xvals[0] = (1 - filterfaktor) * xvals[0] + accx * filterfaktor;
  return xvals[0];
}

float accy_filtered(float accy) {
  yvals[0] = (1 - filterfaktor) * yvals[0] + accy * filterfaktor;
  return yvals[0];
}
