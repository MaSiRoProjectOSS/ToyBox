/**
 * @file serial_usb.cpp
 * @brief usb serial
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "serial_usb.hpp"

#include "../settings.hpp"

////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////
static bool end_text_add_cr = false;

////////////////////////////////////////////////////
// FUNCTION
////////////////////////////////////////////////////
void setup_serial_usb()
{
#if SERIAL_USB_WAIT_UNTIL_CONNECTED
    // Wait until connected
    do {
    } while (!SerialUSB);
#endif
}
bool serial_usb_write(const char value[])
{
    bool result = false;
    ////////////////////////////////////////////////////////////////
    SerialUSB.write(value);
    ////////////////////////////////////////////////////////////////
    return result;
}
bool serial_usb_read(char out_data[])
{
    bool result = false;
    ////////////////////////////////////////////////////////////////
    static char refill[BUFFER_TEXT_SIZE] = { 0 };
    static int read_size                 = 0;
    bool one_sentence                    = false;
    char buffer;
    if (NULL != out_data) {
        out_data[0] = '\0';
        while (SerialUSB.available() > 0) {
            buffer = SerialUSB.read();
            if (0 == buffer) {
            } else {
                if ('\n' == buffer) {
                    one_sentence = true;
                    break;
                } else if ('\r' == buffer) {
                    one_sentence = true;
                    break;
                } else {
                    refill[read_size++] = buffer;
                }
                if ((BUFFER_TEXT_SIZE - 2) <= read_size) {
                    one_sentence = false;
                    read_size    = 0;
                }
            }
        }
        if (true == one_sentence) {
            if (0 < read_size) {
                //
                out_data[0] = '\0';
                for (int i = 0; i < read_size; i++) {
                    out_data[i] = refill[i];
                }
                if (true == end_text_add_cr) {
                    out_data[read_size] = '\n';
                }
                out_data[read_size] = '\0';
                result              = true;
            }
            read_size = 0;
        }
    }
    ////////////////////////////////////////////////////////////////
    return result;
}
