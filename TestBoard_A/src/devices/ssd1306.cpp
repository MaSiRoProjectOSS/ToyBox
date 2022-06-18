/**
 * @file ssd1306.cpp
 * @brief OLED(chip:SSD1309)
 * @date 2022-06-16
 * @ref U8g2 "https://github.com/olikraus/u8g2"
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "ssd1306.hpp"

#include <Arduino.h>
////////////////////////////////////////////////////
// DEFINITION
////////////////////////////////////////////////////
/// fit into the SSD1306_ naming scheme
#define SSD1306_FONT_COLOR_BLACK   0 ///< Draw 'off' pixels
#define SSD1306_FONT_COLOR_WHITE   1 ///< Draw 'on' pixels
#define SSD1306_FONT_COLOR_INVERSE 2 ///< Invert pixels

#define SSD1306_FONT_MODE_TRANSPARENT_NONE 0 ///< none Transparent
#define SSD1306_FONT_MODE_TRANSPARENT      1 ///< Transparent

////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////
#ifndef SSD1306_ENABLE
#define SSD1306_ENABLE 0
#endif

////////////////////////////////////////////////////
// U8G2
////////////////////////////////////////////////////
#if SSD1306_ENABLE
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE); // All Boards without Reset of the Display
#endif

////////////////////////////////////////////////////
// FUNCTION
////////////////////////////////////////////////////
bool ssd1306_write_text(const char value[], int x, int y)
{
    bool result = false;
#if SSD1306_ENABLE
    u8g2.firstPage();
    do {
        u8g2.drawStr(x, y, value);
    } while (u8g2.nextPage());
#endif
    return result;
}

void setup_ssd1306()
{
#if SSD1306_ENABLE
    u8g2.setFontMode(SSD1306_FONT_MODE_TRANSPARENT); // Transparent
    u8g2.setDrawColor(SSD1306_FONT_COLOR_WHITE);
    u8g2.setFont(u8g2_font_8x13_tr);
    u8g2.begin();
#endif
}
