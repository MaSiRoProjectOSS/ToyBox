/**
 * @file usb_serial.cpp
 * @brief usb serial
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "usb_serial.hpp"

/**
 * @brief OUTPUT debug text
 */
#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 0
#endif

////////////////////////////////////////////////////
// FUNCTION
////////////////////////////////////////////////////
void setup_usb_serial()
{
#if USB_USING
    SerialUSB.begin(BAUD_RATE);
#if USB_WAIT_UNTIL_CONNECTED
    // Wait until connected
    do {
    } while (!SerialUSB);
#endif
#if DEBUG_OUTPUT
    char buffer[100];
    sprintf(buffer, "=======\nSTART\n=======\n");
    SerialUSB.write(buffer);
#endif
#endif
}
bool usb_serial_write(String value)
{
    bool result = false;
    ////////////////////////////////////////////////////////////////
    char buffer[255];
    value.toCharArray(buffer, 255);
    SerialUSB.write(buffer);
    ////////////////////////////////////////////////////////////////
    return result;
}
bool usb_serial_read(char **value)
{
    const int BUFFER_TEXT_SIZE           = 255;
    static int cnt                       = 0;
    static char buffer[BUFFER_TEXT_SIZE] = "";
    bool result                          = false;
    ////////////////////////////////////////////////////////////////
    char c = SerialUSB.read();
    if (0 != c) {
        if ('\r' == c) {
        } else if ('\n' == c) {
            buffer[cnt] = '\0';
            result      = true;
        } else {
            buffer[cnt++] = c;
        }
        if (BUFFER_TEXT_SIZE <= cnt) {
            cnt         = 0;
            buffer[cnt] = '\0';
        }
    }
    if (true == result) {
        for (int i = 0; i < cnt; i++) {
            *value[i] = buffer[cnt];
        }
    }

    ////////////////////////////////////////////////////////////////
    return result;
}
