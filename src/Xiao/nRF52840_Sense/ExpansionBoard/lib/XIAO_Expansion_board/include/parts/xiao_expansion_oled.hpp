/**
 * @file xiao_expansion_oled.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_OLED_HPP
#define XIAO_EXPANSION_OLED_HPP

#include "common/common_function.hpp"

#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_OLED
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_OLED 1
#else
#define EXAMPLE_LIBRARY_XIAO_OLED 0
#endif
#endif

class XIAOOled {
public:
    XIAOOled();
    ~XIAOOled();

public:
    bool setup(void);
    U8X8_SSD1306_128X64_NONAME_HW_I2C *Display;

#if EXAMPLE_LIBRARY_XIAO_OLED
public:
    bool example();
#endif

private:
    const unsigned long READ_SPAN_MS = (1 * 1000);
    bool initialize                  = false;
};
} // namespace Parts
} // namespace XIAO

#endif
