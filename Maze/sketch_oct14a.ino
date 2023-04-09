#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";
Servo servo;
Servo servo2;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo.attach(6);
  servo2.attach(8);
  servo.write(90);
  servo2.write(90);
}

void loop() {
  if (radio.available()) {
    int angles[2];
    radio.read(&angles, sizeof(angles));
    Serial.println(angles[1]);
    servo.write(angles[0]);
    servo2.write(angles[1]);
  }
}