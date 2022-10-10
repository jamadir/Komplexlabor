#include <Servo.h>

Servo servox;
Servo servoy;

int val;

void setup() {
  Serial.begin(9600);

  servox.attach(9);
  servoy.attach(6);
}

void loop() {

  int xpot = analogRead(A6);
  int ypot = analogRead(A7);


  float voltagex = xpot * (5.0 / 1023.0);
  float voltagey = ypot * (5.0 / 1023.0);


  Serial.print(voltagex);
  Serial.print(" ");
  Serial.println(voltagey);

  val = map(xpot, 0, 1023, 0, 180);
  servox.write(val);
  val = map(ypot, 0, 1023, 0, 180);
  servoy.write(val);
  delay(15);
}
