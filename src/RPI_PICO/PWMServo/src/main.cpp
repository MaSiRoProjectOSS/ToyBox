
#include <SPI.h>
///////////////////////
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#ifndef PWM_SERVO_PIN_SDA
#define PWM_SERVO_PIN_SDA p12
#endif
#ifndef PWM_SERVO_PIN_SDA
#define PWM_SERVO_PIN_SDA p13
#endif

TwoWire wire(PWM_SERVO_PIN_SDA, PWM_SERVO_PIN_SCL);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_I2C_ADDRESS, wire);

#define US_MIN          500
#define US_MAX          2400
#define SERVO_ANGLE_MIN 0
#define SERVO_ANGLE_MAX 180
#define SERVO_FREQ      50

uint8_t servo_num = 0;
#define SERVO_NUM_MAX 3

void setup()
{
    wire.setTimeout(5000);
    wire.begin();
    delay(3000);
    Serial.println("start!");
    while (!pwm.begin()) {
        Serial.println("Failed to find this chip");
        delay(5000);
    }
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);

    Serial.println("8 channel Servo test!");
    delay(10);
}

void setServoPulse(uint8_t n, double pulse)
{
    double pulse_length = 1000000;
    pulse_length /= SERVO_FREQ;
    Serial.print(pulse_length);
    Serial.println(" us per period");

    pulse_length /= 4096;
    Serial.print(pulse_length);
    Serial.println(" us per bit");
    pulse *= 1000000;
    pulse /= pulse_length;
    Serial.println(pulse);
    pwm.setPWM(n, 0, pulse);
}

void set_angle(int angle)
{
    uint16_t pulse_us = map(angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, US_MIN, US_MAX);

    pwm.writeMicroseconds(servo_num, pulse_us);
}
void loop()
{
    Serial.println("loop!");

    set_angle(SERVO_ANGLE_MIN);
    delay(500);
    set_angle(SERVO_ANGLE_MAX);
    delay(500);
    for (uint16_t microsec = SERVO_ANGLE_MAX; microsec > SERVO_ANGLE_MIN; microsec--) {
        set_angle(microsec);
        delay(1);
    }

    delay(500);

    servo_num++;
    if (servo_num >= SERVO_NUM_MAX) {
        servo_num = 0;
    }
}
