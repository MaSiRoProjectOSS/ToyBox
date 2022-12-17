/**
 * @file xiao_expansion_rtc.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_rtc.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
XIAORtc::XIAORtc()
{
}
XIAORtc::~XIAORtc()
{
}
bool XIAORtc::setup(void)
{
    this->initialize = true;
    return this->initialize;
}
bool XIAORtc::loop(void)
{
    bool result                        = true;
    static unsigned long previous_time = 0;
    if (true == this->initialize) {
        unsigned long current_time = millis();
        if ((this->READ_SPAN_MS + previous_time) < current_time) {
            previous_time = current_time;
        }
    }
    return result;
}

} // namespace Parts
} // namespace XIAO
