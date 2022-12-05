#include <Servo.h>
Servo myservo; // erstellt ein Servo-Objekt, um einen Servomotor zu steuern

void setup() {
  myservo.attach(9); // verknüpft den Servomotor an Pin 9 mit dem Servo-Objekt
}
void loop() {
  
  myservo.write(1); // überträgt die Zielposition an den Servomotors
  delay(1500); // lässt dem Servomotor Zeit, die Zielposition zu erreichen
  myservo.write(179); // überträgt die Zielposition an den Servomotors
  delay(1500); // lässt dem Servomotor Zeit, die Zielposition zu erreichen

}