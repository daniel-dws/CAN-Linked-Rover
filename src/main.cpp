#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>

//Create MPU object
Adafruit_MPU6050 mpu;

//function prototypes
void printReadings(sensors_event_t &a, sensors_event_t &g, sensors_event_t &t);
void plotReadings(sensors_event_t &a, sensors_event_t &g);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 if (mpu.begin()) {
    Serial.println("ESP32 mpu 6050 starting");
 }
//  else {
//    Serial.println("Error starting");
//  }
}

void loop() {
  //Declare 3 event variables
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // printReadings(a, g, t);
  plotReadings(a, g);
  // plotReadings()
}

void printReadings(sensors_event_t &a, sensors_event_t &g, sensors_event_t &t) {
  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2, ");
  Serial.print("Y: "); Serial.print(a.acceleration.y); Serial.print(" m/s^2, ");
  Serial.print("Z: "); Serial.print(a.acceleration.z); Serial.println(" m/s^2");

  Serial.print("Gyro X: "); Serial.print(g.gyro.x); Serial.print(" rad/s, ");
  Serial.print("Y: "); Serial.print(g.gyro.y); Serial.print(" rad/s, ");
  Serial.print("Z: "); Serial.print(g.gyro.z); Serial.println(" rad/s");

  Serial.print("Temperature: "); Serial.print(t.temperature); Serial.println(" degC");
  Serial.println("");
  delay(100);
}

void plotReadings(sensors_event_t &a, sensors_event_t &g) {
  Serial.print(">AccelX:"); Serial.println(a.acceleration.x);
  Serial.print(">AccelY:"); Serial.println(a.acceleration.y);
  Serial.print(">AccelZ:"); Serial.println(a.acceleration.z);
  Serial.print(">GyroX:");  Serial.println(g.gyro.x);
  Serial.print(">GyroY:");  Serial.println(g.gyro.y);
  Serial.print(">GyroZ:");  Serial.println(g.gyro.z);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }