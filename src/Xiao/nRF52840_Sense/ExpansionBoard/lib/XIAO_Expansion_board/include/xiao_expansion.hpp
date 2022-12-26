/**
 * @file xiao_expansion.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_HPP
#define XIAO_EXPANSION_HPP

#include "parts/xiao_expansion_battery.hpp"
#include "parts/xiao_expansion_buzzer.hpp"
#include "parts/xiao_expansion_imu.hpp"
#include "parts/xiao_expansion_led.hpp"
#include "parts/xiao_expansion_oled.hpp"
#include "parts/xiao_expansion_rtc.hpp"
#include "parts/xiao_expansion_user_button.hpp"

namespace XIAO
{
class XIAOExpansion {
public:
    XIAOExpansion();
    ~XIAOExpansion();

public:
    Parts::XIAOLed *Led;
    Parts::XIAOUserButton *UserButton;
    Parts::XIAOImu *Imu;

public:
    // TODO : NOT TESTED DEVICE
    Parts::XIAOBuzzer *Buzzer;
    Parts::XIAOOled *Oled;
    Parts::XIAORtc *Rtc;
    Parts::XIAOBattery *Battery;

    //////////////////////////
    // PDM Microphone
    // 6DoF IMU
    // BLE
    // NFC

    //////////////////////////

    // SPI
    // UART
    // IIC
    // Digital
    // Analog
    // SWD debug
    // Expandable memory
    // Grove connectors
    ///////////////////////////////
    // passive buzzer
    // OLED
    // User button
    // RTC

public:
    bool setup(void);
    bool setup_imu(uint8_t bus_type, uint8_t input_arg);
    bool loop(void);
};
} // namespace XIAO

#endif
