/**
 * @file dip_rotary_switch.cpp
 * @brief
 * @version 0.0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "dip_rotary_switch.hpp"

DIPRotarySwitch::DIPRotarySwitch(int pin_1, int pin_2, int pin_3, int pin_4, bool low_polarity, bool pullup_mode)
{
    this->_pin_1 = pin_1;
    this->_pin_2 = pin_2;
    this->_pin_4 = pin_3;
    this->_pin_8 = pin_4;
    if (true == pullup_mode) {
        pinMode(this->_pin_1, INPUT_PULLUP);
        pinMode(this->_pin_2, INPUT_PULLUP);
        pinMode(this->_pin_4, INPUT_PULLUP);
        pinMode(this->_pin_8, INPUT_PULLUP);
    } else {
        pinMode(this->_pin_1, INPUT_PULLDOWN);
        pinMode(this->_pin_2, INPUT_PULLDOWN);
        pinMode(this->_pin_4, INPUT_PULLDOWN);
        pinMode(this->_pin_8, INPUT_PULLDOWN);
    }
    if (true == low_polarity) {
        this->_polarity = LOW;
    } else {
        this->_polarity = HIGH;
    }
}
int DIPRotarySwitch::get_value()
{
    int bin_1 = (digitalRead(this->_pin_1) == this->_polarity) ? 1 : 0;
    int bin_2 = (digitalRead(this->_pin_2) == this->_polarity) ? 1 : 0;
    int bin_4 = (digitalRead(this->_pin_4) == this->_polarity) ? 1 : 0;
    int bin_8 = (digitalRead(this->_pin_8) == this->_polarity) ? 1 : 0;
    return map(bin_1 + bin_2 * 2 + bin_4 * 4 + bin_8 * 8, //
               this->_from_low,
               this->_from_high,
               this->_to_low,
               this->_to_high);
}

void DIPRotarySwitch::config_map(int from_low, int from_high, int to_low, int to_high)
{
    this->_from_low  = from_low;
    this->_from_high = from_high;
    this->_to_low    = to_low;
    this->_to_high   = to_high;
}
