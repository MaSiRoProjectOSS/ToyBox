/**
 * @file xiao_expansion_buzzer.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_buzzer.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
XIAOBuzzer::XIAOBuzzer() : initialize(false)
{
}
XIAOBuzzer::~XIAOBuzzer()
{
}
void XIAOBuzzer::_playTone(int tone, int duration)
{
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(this->SPEAKER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(this->SPEAKER_PIN, LOW);
        delayMicroseconds(tone);
    }
}

void XIAOBuzzer::_playNote(char note, int duration)
{
    char names[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'x', 'y' };
    int tones[]  = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 834, 765, 593, 468, 346, 224, 655, 715 };
    int SPEE     = 5;

    // play the tone corresponding to the note name

    for (int i = 0; i < 16; i++) {
        if (names[i] == note) {
            int new_duration = duration / SPEE;
            this->_playTone(tones[i], new_duration);
        }
    }
}

bool XIAOBuzzer::setup(void)
{
    pinMode(this->SPEAKER_PIN, OUTPUT);
    this->initialize = true;
    return this->initialize;
}

bool XIAOBuzzer::loop(void)
{
    if (true == this->initialize) {
        for (int i = 0; i < length; i++) {
            if (notes[i] == ' ') {
                delay(beats[i] * tempo); // reset
            } else {
                this->_playNote(notes[i], beats[i] * tempo);
            }
            // pause between notes
            delay(tempo);
        }
    }
    return true;
}
} // namespace Parts
} // namespace XIAO
