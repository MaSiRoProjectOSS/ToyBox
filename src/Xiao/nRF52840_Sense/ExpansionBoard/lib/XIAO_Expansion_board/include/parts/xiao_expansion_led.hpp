/**
 * @file xiao_expansion_led.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_LED_HPP
#define XIAO_EXPANSION_LED_HPP

#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_LED
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_LED 1
#else
#define EXAMPLE_LIBRARY_XIAO_LED 0
#endif
#endif

class CtrlLED {
public:
    CtrlLED(pin_size_t pin);
#if 0
     PinStatus operator=(int value);
#endif
    PinStatus set(int value);
    PinStatus get();
    PinStatus on();
    PinStatus off();

private:
    PinStatus set_pin(int value);
    PinStatus get_pin();

private:
    pin_size_t LED_PIN = 0;
};

class XIAOLed {
public:
    XIAOLed();
    ~XIAOLed();

public:
    CtrlLED *RED;
    CtrlLED *GREEN;
    CtrlLED *BLUE;

public:
    void all_clear();
    void all_bride();

#if EXAMPLE_LIBRARY_XIAO_LED
public:
    bool example();
    const unsigned long READ_SPAN_MS = (2 * 1000);
#endif

private:
};
} // namespace Parts
} // namespace XIAO

#endif
