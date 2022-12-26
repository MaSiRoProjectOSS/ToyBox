/**
 * @file xiao_expansion_user_button.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_user_button.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
XIAOUserButton::XIAOUserButton()
{
    pinMode(this->PIN, INPUT_PULLUP);
}
XIAOUserButton::~XIAOUserButton()
{
}
bool XIAOUserButton::setup()
{
    this->initialize = true;
    return this->initialize;
}

PinStatus XIAOUserButton::get()
{
    return digitalRead(this->PIN);
}

#if EXAMPLE_LIBRARY_XIAO_USER_BUTTON
bool XIAOUserButton::example(void)
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

#endif
} // namespace Parts
} // namespace XIAO
