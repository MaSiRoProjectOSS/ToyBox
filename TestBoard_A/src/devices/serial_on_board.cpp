/**
 * @file serial_on_board.cpp
 * @brief serial on board
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "serial_on_board.hpp"

#include "../settings.hpp"

////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////
static bool end_text_add_cr = false;

////////////////////////////////////////////////////
// FUNCTION
////////////////////////////////////////////////////
void setup_serial_on_board()
{
#ifdef SERIAL_ON_BOARD_BAUDRATE
    Serial1.begin(SERIAL_ON_BOARD_BAUDRATE);
#ifdef SERIAL_ON_BOARD_WAIT_UNTIL_CONNECTED
    do {
    } while (!Serial1);
#endif
#endif
    //
}

bool serial_on_board_write(const char value[])
{
    bool result = false;
#ifdef SERIAL_ON_BOARD_BAUDRATE
    ////////////////////////////////////////////////////////////////
    Serial1.write(value);
    ////////////////////////////////////////////////////////////////
#endif
    return result;
}

bool serial_on_board_read(char *out_data[])
{
    bool result = false;
#ifdef SERIAL_ON_BOARD_BAUDRATE
    ////////////////////////////////////////////////////////////////
    static char refill[BUFFER_TEXT_SIZE] = { 0 };
    static int read_size                 = 0;
    bool flag_repeat                     = true;
    bool one_sentence                    = false;
    char buffer;
    if (NULL != *out_data) {
        *out_data[0] = '\0';
        do {
            buffer = Serial1.read();
            if (0 == buffer) {
                flag_repeat = false;
            } else {
                if ('\n' == buffer) {
                    flag_repeat  = false;
                    one_sentence = true;
                    break;
                } else if ('\r' == buffer) {
                    flag_repeat  = false;
                    one_sentence = true;
                    break;
                } else {
                    refill[read_size++] = buffer;
                }
                if ((BUFFER_TEXT_SIZE - 2) <= read_size) {
                    flag_repeat  = false;
                    one_sentence = false;
                    read_size    = 0;
                }
            }
        } while (true == flag_repeat);
        if (true == one_sentence) {
            if (0 < read_size) {
                //
                *out_data[0] = '\0';
                for (int i = 0; i < read_size; i++) {
                    *out_data[i] = refill[i];
                }
                if (true == end_text_add_cr) {
                    *out_data[read_size] = '\n';
                }
                *out_data[read_size] = '\0';
                result               = true;
            }
            read_size = 0;
        }
    }
    ////////////////////////////////////////////////////////////////
#endif
    return result;
}
