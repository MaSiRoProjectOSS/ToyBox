/**
 * @file serial_usb.hpp
 * @brief usb serial
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef SERIAL_USB_HPP
#define SERIAL_USB_HPP
#include <Arduino.h>

void setup_serial_usb();
bool serial_usb_write(const char value[]);
bool serial_usb_read(char *out_data[]);

#endif
