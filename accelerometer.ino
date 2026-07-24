#include <Arduino_LSM9DS1.h>

float x, y, z;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("IMU initialized");

  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // RGB LEDs are active LOW
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {
  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    // Send values to Serial Plotter
    Serial.print("X:");
    Serial.print(x);
    Serial.print(" ");

    Serial.print("Y:");
    Serial.print(y);
    Serial.print(" ");

    Serial.print("Z:");
    Serial.println(z);

    // LED indication based on orientation
    if (y > x && y > z) {
      // Red
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, HIGH);

    } else if (y < x && y < z) {
      // Blue
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDB, LOW);

    } else if (z > x && z > y) {
      // Purple (Red + Blue)
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
    }

    delay(50);
  }
}