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
#include "../settings.hpp"

#include <Arduino.h>

class OledForSSD1306 {
private:
    const int release_display_max = 10000 / LOOP_DELAY_MS;
    int release_display_cnt       = release_display_max;
    bool release_display_flag     = false;

public:
    void setup();
    void loop();
    bool write_text(const char *value, int x, int y);
    void clear(void);
void    set_display_flag(void);
};

#endif
