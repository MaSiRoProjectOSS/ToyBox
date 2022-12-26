/**
 * @file xiao_expansion_led.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_led.hpp"

namespace XIAO
{
namespace Parts
{

////////////////////////////////////////////
CtrlLED::CtrlLED(pin_size_t pin)
{
    this->LED_PIN = pin;
    pinMode(this->LED_PIN, OUTPUT);
}

#if 0
PinStatus CtrlLED::operator=(int value)
{
    return set_pin(value);
}
#endif
PinStatus CtrlLED::on()
{
    return this->set(1);
}
PinStatus CtrlLED::off()
{
    return this->set(0);
}
PinStatus CtrlLED::set(int value)
{
    return set_pin(value);
}
PinStatus CtrlLED::get()
{
    return get_pin();
}

PinStatus CtrlLED::set_pin(int value)
{
    switch (value) {
        case 0:
            digitalWrite(this->LED_PIN, HIGH);
            break;

        default:
            digitalWrite(this->LED_PIN, LOW);
            break;
    }
    return get_pin();
}
PinStatus CtrlLED::get_pin()
{
    return digitalRead(this->LED_PIN);
}

////////////////////////////////////////////

XIAOLed::XIAOLed()
{
    this->RED   = new CtrlLED(LEDR);
    this->GREEN = new CtrlLED(LEDG);
    this->BLUE  = new CtrlLED(LEDB);
}
XIAOLed::~XIAOLed()
{
}
void XIAOLed::all_clear()
{
    this->RED->off();
    this->GREEN->off();
    this->BLUE->off();
}
void XIAOLed::all_bride()
{
    this->RED->on();
    this->GREEN->on();
    this->BLUE->on();
}

#if EXAMPLE_LIBRARY_XIAO_LED
bool XIAOLed::example(void)
{
    static int count = 0;
    count++;
    static unsigned long previous_time = 0;
    if (true == this->initialize) {
        unsigned long current_time = millis();
        if ((this->READ_SPAN_MS + previous_time) < current_time) {
            previous_time = current_time;

            char buffer[255];
            switch (count) {
                case 1:
                    this->RED->on();
                    sprintf(buffer, "LED : RED : ON : %d", count);
                    break;
                case 2:
                    this->RED->off();
                    sprintf(buffer, "LED : RED : OFF : %d", count);
                    break;
                case 3:
                    this->BLUE->on();
                    sprintf(buffer, "LED : BLUE : ON : %d", count);
                    break;
                case 4:
                    this->BLUE->off();
                    sprintf(buffer, "LED : BLUE : OFF : %d", count);
                    break;
                case 5:
                    this->GREEN->on();
                    sprintf(buffer, "LED : GREEN : ON : %d", count);
                    break;
                case 6:
                default:
                    this->GREEN->off();
                    sprintf(buffer, "LED : GREEN : OFF : %d", count);
                    count = 0;
                    break;
            }
            CommonFunction::output_message(false, buffer);
        }
    }
    bool result = true;
    return result;
}
#endif
} // namespace Parts
} // namespace XIAO
