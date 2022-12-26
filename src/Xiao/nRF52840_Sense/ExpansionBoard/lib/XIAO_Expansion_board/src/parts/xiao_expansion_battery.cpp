/**
 * @file xiao_expansion_battery.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_battery.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
XIAOBattery::XIAOBattery()
{
}
XIAOBattery::~XIAOBattery()
{
}

bool XIAOBattery::setup(BatteryType battery_type)
{
    // pinMode(this->BATTERY_PIN, OUTPUT);
    this->type       = battery_type;
    this->initialize = true;
    return this->initialize;
}
float XIAOBattery::_get_pad()
{
    static float previous = 0;
    float value           = 0;

    if (true == this->initialize) {
        float pin_value = (float)analogRead(this->BATTERY_PIN);
        float value     = (5000.0 * pin_value) / 1024.0;
        previous        = value;
    }
    return previous;
}
float XIAOBattery::_get_expansion_board()
{
    static float previous = 0;
    float value           = 0;
    if (true == this->initialize) {
        // TODO
        previous = value;
    }
    return previous;
}

float XIAOBattery::get()
{
    static float previous = 0;
    float value           = 0;
    if (true == this->initialize) {
        unsigned long current_time = millis();
        if ((this->read_time + this->READ_SPAN_MS) <= current_time) {
            switch (this->type) {
                case BatteryType::BatteryType_Expansion_Board:
                    previous = this->_get_expansion_board();
                    break;
                default:
                    previous = this->_get_pad();
                    break;
            }
        }
    }
    return previous;
}
unsigned long XIAOBattery::get_time()
{
    return this->read_time;
}
float XIAOBattery::operator=(int value)
{
    return this->get();
}
} // namespace Parts
} // namespace XIAO
