/**
 * @file ssd1306.hpp
 * @brief OLED(chip:SSD1309)
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef SSD1306_HPP
#define SSD1306_HPP
#include <Arduino.h>

void setup_ssd1306();
bool ssd1306_write_text(const char *value, int x, int y);

#endif
