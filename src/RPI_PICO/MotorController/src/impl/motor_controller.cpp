/**
 * @file motor_controller.cpp
 * @brief
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "motor_controller.hpp"

MotorController::MotorController(int pin)
{
    this->index = this->servo.attach(pin, this->MIN_PULSE, this->MAX_PULSE);
}

void MotorController::set_speed(int speed)
{
    if (speed < this->MIN_ANGLE) {
        speed = this->MIN_ANGLE;
    } else if (speed > this->MAX_ANGLE) {
        speed = this->MAX_ANGLE;
    }
    this->servo.write(speed);
}

// なんか、900～2100+7usec以上という感じで、7usecで堕ちるタイミングを図っている感じ。
// SG 90はPWMで20ms中、0.5～2.4msのパルスを送ることで、0～180度の角度を指定できる。
// Miuzei MS18は、PWMで20ms中、0.9～2.1msのパルスを送ることで、0～180度の角度を指定できる。
