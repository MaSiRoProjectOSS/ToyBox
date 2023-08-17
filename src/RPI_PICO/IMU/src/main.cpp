#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
#define IMU_PIN_SDA p18
#define IMU_PIN_SCL p19
#define IMU_PIN_INT p20
TwoWire wire(IMU_PIN_SDA, IMU_PIN_SCL);

void setup()
{
    delay(3000);
    if (!mpu.begin(MPU6050_I2CADDR_DEFAULT, &wire)) {
        while (1) {
            Serial.println("Failed to find MPU6050 chip");
            delay(3000);
        }
    }
    Serial.println("Found a MPU-6050 sensor");

    //setup motion detection
    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    mpu.setMotionDetectionThreshold(1);
    mpu.setMotionDetectionDuration(20);
    mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
    mpu.setInterruptPinPolarity(true);
    mpu.setMotionInterrupt(true);
}

void loop()
{
    sensors_event_t a, g, temp;
    if (mpu.getMotionInterruptStatus()) {
        mpu.getEvent(&a, &g, &temp);

        Serial.print("Accelerometer ");
        Serial.print("X: ");
        Serial.print(a.acceleration.x, 1);
        Serial.print(" m/s^2, ");
        Serial.print("Y: ");
        Serial.print(a.acceleration.y, 1);
        Serial.print(" m/s^2, ");
        Serial.print("Z: ");
        Serial.print(a.acceleration.z, 1);
        Serial.print(" m/s^2");
        Serial.print("\t\t");

        Serial.print("Gyroscope ");
        Serial.print("X: ");
        Serial.print(g.gyro.x, 1);
        Serial.print(" rps, ");
        Serial.print("Y: ");
        Serial.print(g.gyro.y, 1);
        Serial.print(" rps, ");
        Serial.print("Z: ");
        Serial.print(g.gyro.z, 1);
        Serial.println(" rps");

        delay(1000);
    }
}
