/**
 * @file xiao_expansion_oled.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_oled.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
XIAOOled::XIAOOled() : initialize(false)
{
}
XIAOOled::~XIAOOled()
{
}
bool XIAOOled::setup(void)
{
    bool result = false;

    this->Display = new U8X8_SSD1306_128X64_NONAME_HW_I2C(PIN_WIRE_SCL, PIN_WIRE_SDA, U8X8_PIN_NONE);
    if (true == this->Display->begin()) {
        this->Display->setFlipMode(1);
        // this->Display->setFont(u8x8_font_chroma48medium8_r);
        this->Display->setFont(u8x8_font_7x14B_1x2_f);
        result = true;
    }
    this->initialize = result;
    return this->initialize;
}

#if EXAMPLE_LIBRARY_XIAO_OLED

bool XIAOOled::example(void)
{
    static int col                     = 0;
    bool result                        = true;
    static unsigned long previous_time = 0;
    if (true == this->initialize) {
        unsigned long current_time = millis();
        if ((this->READ_SPAN_MS + previous_time) < current_time) {
            previous_time             = current_time;
            static const String words = "Hello World!";
            int len                   = words.length();
            this->Display->setCursor(-col, 0);
            this->Display->print(words);
            col++;
            if (col > len) {
                col = 0;
            }
        }
    }
    return result;
}
#endif
} // namespace Parts
} // namespace XIAO
