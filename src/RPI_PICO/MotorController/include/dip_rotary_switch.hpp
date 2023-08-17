/**
 * @file dip_rotary_switch.hpp
 * @brief
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef DIP_ROTARY_SWITCH_HPP
#define DIP_ROTARY_SWITCH_HPP

#include <Arduino.h>

class DIPRotarySwitch {
public:
    DIPRotarySwitch(int pin_1, int pin_2, int pin_3, int pin_4, bool low_polarity = true, bool pullup_mode = true);

    int get_value();
    void config_map(int from_low, int from_high, int to_low, int to_high);

private:
    int _pin_1;
    int _pin_2;
    int _pin_4;
    int _pin_8;
    int _polarity = LOW;

    int _from_low  = 0;
    int _from_high = 15;
    int _to_low    = 0;
    int _to_high   = 100;
};
#endif
