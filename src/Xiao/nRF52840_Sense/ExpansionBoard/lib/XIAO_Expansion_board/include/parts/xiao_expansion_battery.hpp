/**
 * @file xiao_expansion_battery.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_BATTERY_HPP
#define XIAO_EXPANSION_BATTERY_HPP

#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_BATTERY
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_BATTERY 1
#else
#define EXAMPLE_LIBRARY_XIAO_BATTERY 0
#endif
#endif

class XIAOBattery {
public:
    enum BatteryType
    {
        BatteryType_Pad,
        BatteryType_Expansion_Board,
    };

public:
    XIAOBattery();
    ~XIAOBattery();

public:
    bool setup(BatteryType battery_type = BatteryType::BatteryType_Expansion_Board);

public:
    unsigned long get_time();
    float get();
    float operator=(int value);
    bool initialize = false;

private:
    float _get_pad();
    float _get_expansion_board();

    const unsigned long READ_SPAN_MS = (5 * 1000);
    const pin_size_t BATTERY_PIN     = PIN_VBAT;
    unsigned long read_time          = 0;
    BatteryType type                 = BatteryType::BatteryType_Expansion_Board;
};
} // namespace Parts
} // namespace XIAO

#endif
