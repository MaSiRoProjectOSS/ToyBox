/**
 * @file rn4020_serial.hpp
 * @brief BLE(chip:RN4020)
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef RN4020_serial_HPP
#define RN4020_serial_HPP
#include <Arduino.h>

void setup_rn4020_serial();
bool rn4020_serial_write(char *value);
bool rn4020_serial_read(char **value);

#endif
