/**
 * @file main.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>
#include <xiao_expansion.hpp>

using namespace XIAO;

XIAOExpansion xiao;

void setup()
{
    xiao.setup();
    xiao.setup_imu(I2C_MODE, 0x6A);
}

void loop()
{
    char buffer[255];
    static int READ_SPAN_MS            = 500;
    bool result                        = true;
    static unsigned long previous_time = 0;

    unsigned long current_time = millis();
    if ((READ_SPAN_MS + previous_time) < current_time) {
        previous_time = current_time;
        xiao.loop();
    }
}