#include "Wire.h" 

#define MPU6050_GYRO_CONFIG       0x1B ///< Gyro specfic configuration register

typedef enum {
  MPU6050_GYR_RANGE_250,  // +/- 250 deg/s (default)
  MPU6050_GYR_RANGE_500,  // +/- 500 deg/s
  MPU6050_GYR_RANGE_1000, // +/- 1000 deg/s
  MPU6050_GYR_RANGE_2000  // +/- 2000 deg/s
} mpu6050_gyr_range;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  MPU6050_wakeUp();
 
  setGyrRange(MPU6050_GYR_RANGE_250);
}
void loop() {
  MPU6050_wakeUp();

  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. 
                               // As a result, the connection is kept active.
  Wire.requestFrom(MPU6050_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  
  gyroX = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyroY = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyroZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  
  // print out data

  Serial.print(" | GyX = "); Serial.print(toStr(gyroX));
  Serial.print(" | GyY = "); Serial.print(toStr(gyroY));
  Serial.print(" | GyZ = "); Serial.print(toStr(gyroZ));
  Serial.println();
  
  delay(1000);
}
char* toStr(int16_t i) { // int16 to string plus output format
  sprintf(result, "%6d", i);
  return result;
}
void setAccRange(mpu6050_acc_range range){
  writeRegister(MPU6050_ACCEL_CONFIG, range<<3);
}
void setGyrRange(mpu6050_gyr_range range){
  writeRegister(MPU6050_GYRO_CONFIG, range<<3);
}
void MPU6050_wakeUp(){
  writeRegister(MPU6050_PWR_MGT_1, 0); 
  delay(30); // give him time to wake up, gyro needs quite a while to stabilize;
}
void MPU6050_sleep(){
  writeRegister(MPU6050_PWR_MGT_1, 1<<MPU6050_SLEEP); 
}
void writeRegister(uint16_t reg, byte value){
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg); 
  Wire.write(value); 
  Wire.endTransmission(true);
}