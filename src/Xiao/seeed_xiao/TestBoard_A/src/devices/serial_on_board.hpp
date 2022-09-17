/**
 * @file serial_on_board.hpp
 * @brief serial on board
 * @date 2022-06-16
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef SERIAL_ON_BOARD_HPP
#define SERIAL_ON_BOARD_HPP
#include <Arduino.h>

void setup_serial_on_board();
bool serial_on_board_write(const char value[]);
bool serial_on_board_read(char out_data[]);

#endif
