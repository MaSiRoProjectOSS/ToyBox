/**
 * @file motor_controller.hpp
 * @brief
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include <Servo.h>

class MotorController {
public:
    MotorController(int pin);

    void set_speed(int speed);

private:
    int index;
    Servo servo;
    const int MIN_PULSE = 900;
    const int MAX_PULSE = 2100;
    const int MIN_ANGLE = 0;
    const int MAX_ANGLE = 120;
};

#endif // MOTOR_CONTROLLER_HPP
