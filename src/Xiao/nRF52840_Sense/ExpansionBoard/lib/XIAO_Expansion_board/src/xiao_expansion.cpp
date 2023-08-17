/**
 * @file xiao_expansion.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "xiao_expansion.hpp"

#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
///////////////////////////////////////

XIAOExpansion::XIAOExpansion()
{
    Led        = new Parts::XIAOLed();
    Buzzer     = new Parts::XIAOBuzzer();
    Oled       = new Parts::XIAOOled();
    Rtc        = new Parts::XIAORtc();
    UserButton = new Parts::XIAOUserButton();
    Battery    = new Parts::XIAOBattery();
    Imu        = new Parts::XIAOImu();
}
XIAOExpansion::~XIAOExpansion()
{
}
bool XIAOExpansion::setup_imu(uint8_t bus_type, uint8_t input_arg)
{
    bool result = true;
    this->Imu->setup(new LSM6DS3(bus_type, input_arg));
    return result;
}
bool XIAOExpansion::setup(void)
{
    char buffer[255];
    sprintf(buffer, "  BOARD_NAME : %s", BOARD_NAME);

    CommonFunction::output_message(false, "==========");
    CommonFunction::output_message(false, buffer);
    CommonFunction::output_message(false, "==========");
    ////////////////////////////////////////////////////
    this->Led->all_clear();
    this->UserButton->setup();
    this->Oled->setup();
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // TODO : NOT TESTED DEVICE
    ////////////////////////////////////////////////////
#if 0
    this->Buzzer->setup();
    this->Rtc->setup();
    this->Battery->setup();
#endif
    return true;
}

bool XIAOExpansion::loop(void)
{
    char buffer[255];
#if EXAMPLE_LIBRARY_XIAO_LED
    this->Led->example();
    static PinStatus last_led_r_status = LOW;
    static PinStatus last_led_b_status = LOW;
    static PinStatus last_led_g_status = LOW;
    PinStatus current_led_r_status     = this->Led->RED->get();
    PinStatus current_led_b_status     = this->Led->BLUE->get();
    PinStatus current_led_g_status     = this->Led->GREEN->get();
    if ((last_led_b_status != current_led_b_status) || (last_led_r_status != current_led_r_status) || (last_led_g_status != current_led_g_status)) {
        last_led_b_status = current_led_b_status;
        last_led_r_status = current_led_r_status;
        last_led_g_status = current_led_g_status;
        sprintf(buffer,
                "LED : RED[%s]/BLUE[%s]/GREEN[%s]",
                ((HIGH == current_led_r_status) ? "OFF" : " ON"),
                ((HIGH == current_led_b_status) ? "OFF" : " ON"),
                ((HIGH == current_led_g_status) ? "OFF" : " ON"));
        CommonFunction::output_message(false, buffer);
    }
#endif
#if EXAMPLE_LIBRARY_XIAO_USER_BUTTON
    static PinStatus last_button_status = LOW;
    PinStatus current_button_states     = this->UserButton->get();
    if (current_button_states == HIGH) {
        this->Led->BLUE->off();
    } else {
        this->Led->BLUE->on();
    }
    if (last_button_status != current_button_states) {
        last_button_status = current_button_states;
        sprintf(buffer, "BUTTON : [%s]", ((HIGH == this->UserButton->get()) ? "OFF" : " ON"));
        CommonFunction::output_message(false, buffer);
    }
#endif
#if EXAMPLE_LIBRARY_XIAO_IMU
    this->Imu->loop();
#endif
#if EXAMPLE_LIBRARY_XIAO_OLED
    this->Oled->loop();
#endif
    //////////////////////////////////
    // TODO : TEST
    //////////////////////////////////

#if EXAMPLE_LIBRARY_XIAO_BUZZER
    this->Buzzer->loop();
#endif
#if EXAMPLE_LIBRARY_XIAO_RTC
    this->Rtc->loop();
#endif
#if EXAMPLE_LIBRARY_XIAO_BATTERY
#endif

    return true;
}
///////////////////////////////////////
} // namespace XIAO
