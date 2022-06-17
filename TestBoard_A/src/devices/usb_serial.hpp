/**
 * @file usb_serial.hpp
 * @brief usb serial
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef USB_SERIAL_HPP
#define USB_SERIAL_HPP
#include <Arduino.h>

void setup_usb_serial();
bool usb_serial_write(String value);
bool usb_serial_read(char **value);

#endif
