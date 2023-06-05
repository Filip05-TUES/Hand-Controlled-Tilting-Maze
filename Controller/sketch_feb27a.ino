#include <Adafruit_MPU6050.h>
#include <nRF24L01.h>
#include <RF24.h>

Adafruit_MPU6050 srituhobby;
RF24 radio(7, 8);
const byte address[6] = "00001";

float prevX;
float smoothX;
float prevY;
float smoothY;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Wire.begin();
  srituhobby.begin();

  srituhobby.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  srituhobby.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  srituhobby.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  srituhobby.getEvent(&a, &g, &temp);

  int valueX = map(a.acceleration.x,  -10, 10, 180, 0);
  int valueY = map(a.acceleration.y,  -10, 10, 180, 0);

  smoothX = valueX * 0.05 + prevX * 0.95;
  smoothY = valueY * 0.05 + prevY * 0.95;
  prevX = smoothX;
  prevY = smoothY;
  
  int angles[] = {smoothX, smoothY};
  radio.write(&angles, sizeof(angles));
}
