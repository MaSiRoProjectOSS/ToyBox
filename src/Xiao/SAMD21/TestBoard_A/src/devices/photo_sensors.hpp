/**
 * @file photo_sensors.hpp
 * @brief photo_sensors
 * @date 2022-06-17
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef PHOTO_SENSORS_HPP
#define PHOTO_SENSORS_HPP
#include <Arduino.h>

#define PHOTO_SENSORS_NUM 5

class PhotoSensors {
public:
    PhotoSensors();
    ////////////////////////////////////////////////////
    // enum
    ////////////////////////////////////////////////////
    typedef enum
    {
        STATE_PHOTO_SENSORS_UNKNOWN,
        STATE_PHOTO_SENSORS_DETECTION,
        STATE_PHOTO_SENSORS_DETECTING,
        STATE_PHOTO_SENSORS_DETECTED,
        STATE_PHOTO_SENSORS_LOST,
    } STATE_PHOTO_SENSORS;
    // ==================================================== //

    void setup();
    int get_mode(int *mode);

private:
    bool get_pin_state(uint32_t pin_value);

    ////////////////////////////////////////////////////
    // HARDWARE SETTINGS
    ////////////////////////////////////////////////////
    const uint8_t PIN_OUTPUT_STATUS = LOW;

    ////////////////////////////////////////////////////
    // SOFTWARE SETTINGS
    ////////////////////////////////////////////////////
    const int DigitalAnalogPin_NUM = PHOTO_SENSORS_NUM;
    /**
     * @brief DETECTION_PIN_NUMBER
     */
    int pin_analog[PHOTO_SENSORS_NUM] = { -1 };

    STATE_PHOTO_SENSORS flagState;
    int cntDetection;
    int cntRelease;
    bool flagDetect_previous[PHOTO_SENSORS_NUM];
};
#endif
