/**
 * @file main.cpp
 * @brief
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "dip_rotary_switch.hpp"
#include "motor_controller.hpp"

MotorController motor_controller(PIN_PWM);
DIPRotarySwitch rotary(PIN_ROTARY_1, //
                       PIN_ROTARY_2,
                       PIN_ROTARY_3,
                       PIN_ROTARY_4,
                       LOW_POLARITY,
                       PULLUP_MODE);

void setup()
{
    Serial.print("setup\n");
    rotary.config_map(0, 15, 0, 120);
}

void loop()
{
    static int previous_speed = -1;
    int speed                 = rotary.get_value();

    if (speed != previous_speed) {
        previous_speed = speed;
        motor_controller.set_speed(speed);
        Serial.println(speed);
    }
    Serial.print("loop\n");

    sleep_ms(1000);
}
