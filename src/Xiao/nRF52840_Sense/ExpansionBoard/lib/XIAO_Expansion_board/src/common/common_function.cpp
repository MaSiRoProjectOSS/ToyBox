/**
 * @file common_function.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 *
 * @copyright Copyright (c) 2022 / MaSiRo Project.
 *
 */
#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
void CommonFunction::output_message(bool message_type_is_error, const char *message, bool add_header)
{
#ifndef LOG_VERBOSE
    if (true == message_type_is_error)
#endif
    {
        if (true == add_header) {
            char buffer[300];
            unsigned long tm    = millis();
            unsigned long tm_s  = tm / 1000;
            unsigned long tm_ms = tm % 1000;

            if (true == message_type_is_error) {
                sprintf(buffer, "[Error] [%7ld.%03ld] : %s", tm_s, tm_ms, message);
            } else {
                sprintf(buffer, "[     ] [%7ld.%03ld] : %s", tm_s, tm_ms, message);
            }
            SerialUSB.println(buffer);
        } else {
            SerialUSB.println(message);
        }
    }
}
} // namespace XIAO
