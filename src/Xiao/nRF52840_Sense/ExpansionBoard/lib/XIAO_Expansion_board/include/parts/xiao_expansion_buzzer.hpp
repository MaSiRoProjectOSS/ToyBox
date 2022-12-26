/**
 * @file xiao_expansion_buzzer.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_BUZZER_HPP
#define XIAO_EXPANSION_BUZZER_HPP

#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_BUZZER
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_BUZZER 1
#else
#define EXAMPLE_LIBRARY_XIAO_BUZZER 0
#endif
#endif

class XIAOBuzzer {
public:
    XIAOBuzzer();
    ~XIAOBuzzer();

public:
    bool setup(void);
    bool loop(void);

private:
    void _playTone(int tone, int duration);
    void _playNote(char note, int duration);

private:
    const int SPEAKER_PIN = A3;
    bool initialize       = false;

private:
    const unsigned long READ_SPAN_MS = (5 * 1000);
    int length                       = 31; // the number of notes
    char notes[255]                  = "GGAGcB GGAGdc GGxecBA yyecdc     ";
    int beats[255]                   = {
                          2, 2, 8, 8, 8, 16, 1,  // GGAGcB
                          2, 2, 8, 8, 8, 16, 1,  // GGAGdc
                          2, 2, 8, 8, 8, 8,  16, // GGxecBA
                          1, 2, 2, 8, 8, 8,  16, // yyecdc
                          1, 1, 1, 1             //
    };
    int tempo = 170;
};
} // namespace Parts
} // namespace XIAO

#endif
