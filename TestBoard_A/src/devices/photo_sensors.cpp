/**
 * @file photo_sensors.cpp
 * @brief
 * @date 2022-06-17
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "photo_sensors.hpp"

#include "../settings.hpp"

#include <Arduino.h>

////////////////////////////////////////////////////
// REDEFINITION
////////////////////////////////////////////////////
#ifndef DETECTION_PIN_NUMBER_1
#define DETECTION_PIN_NUMBER_1 -1
#endif
#ifndef DETECTION_PIN_NUMBER_2
#define DETECTION_PIN_NUMBER_2 -1
#endif
#ifndef DETECTION_PIN_NUMBER_3
#define DETECTION_PIN_NUMBER_3 -1
#endif
#ifndef DETECTION_PIN_NUMBER_4
#define DETECTION_PIN_NUMBER_4 -1
#endif
#ifndef DETECTION_PIN_NUMBER_5
#define DETECTION_PIN_NUMBER_5 -1
#endif

////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////
#define PHOTO_SENSORS_PIN_RANGE_MIN 0
#define PHOTO_SENSORS_PIN_RANGE_MAX 10

////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////
/**
 * @brief Get the pin state object
 *
 * @param pin_value
 * @param buffer
 * @return true
 * @return false
 */
bool PhotoSensors::get_pin_state(uint32_t pin_value)
{
    bool result     = false;
    int buttonState = digitalRead(pin_value);
    if (PIN_OUTPUT_STATUS == buttonState) {
#if DEBUG_OUTPUT_FOR_USB_SERIAL
        char text[255];
        sprintf(text, " - buttonState[%ld]\n", pin_value);
        SerialUSB.write(text);
#endif
        result = true;
    }
    return result;
}
// ==================================================== //
PhotoSensors::PhotoSensors()
{
    bool flag           = false;
    this->pin_analog[0] = DETECTION_PIN_NUMBER_1;
    this->pin_analog[1] = DETECTION_PIN_NUMBER_2;
    this->pin_analog[2] = DETECTION_PIN_NUMBER_3;
    this->pin_analog[3] = DETECTION_PIN_NUMBER_4;
    this->pin_analog[4] = DETECTION_PIN_NUMBER_5;

    for (int i = 0; i < this->DigitalAnalogPin_NUM; i++) {
        flag = false;
        if (PHOTO_SENSORS_PIN_RANGE_MIN > this->pin_analog[i]) {
            flag = true;
        } else if (PHOTO_SENSORS_PIN_RANGE_MAX < this->pin_analog[i]) {
            flag = true;
        } else {
            // do nothing
        }
        if (true == flag) {
            this->pin_analog[i] = -1;
        }
    }
}
////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////
void PhotoSensors::setup()
{
    this->flagState                              = STATE_PHOTO_SENSORS_LOST;
    this->cntDetection                           = 0;
    this->cntRelease                             = DETECTION_RELEASE_TIME_MS / LOOP_DELAY_MS;
    this->flagDetect_previous[PHOTO_SENSORS_NUM] = { false };

    for (int i = 0; i < this->DigitalAnalogPin_NUM; i++) {
        if (-1 != this->pin_analog[i]) {
            pinMode(this->pin_analog[i], INPUT);
        }
    }
}

/**
 * @brief Detect changes when  digital-in changes at one-second intervals.
 *
 * @return int  The sensor number detected is expressed in bits.
 *              If it is lost, return 'STATE_PHOTO_SENSORS'.
 */
int PhotoSensors::get_mode(int *mode)
{
    bool flagDetect[DigitalAnalogPin_NUM] = { false };
    int result                            = 0;
    bool flagDone                         = false;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
    String str_append = "";
    char buffer[150];
    char delimiter               = '[';
    static unsigned long elapsed = 0;
#endif
    *mode = 0;
    for (int i = 0; i < this->DigitalAnalogPin_NUM; i++) {
        if (-1 != this->pin_analog[i]) {
            flagDetect[i] = get_pin_state(this->pin_analog[i]);
        }
    }
    // determine whether to process
    for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
        if (true == flagDetect[i]) {
            flagDone = true;
        }
    }

    if ((true == flagDone)) {
        // The sensors detected.
        switch (flagState) {
            case STATE_PHOTO_SENSORS_LOST:
                if ((DETECTION_WAITING_TIME_MS / LOOP_DELAY_MS) <= cntDetection) {
                    flagState = STATE_PHOTO_SENSORS_DETECTION;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                    elapsed = millis();
#else
#endif
                    cntRelease = DETECTION_RELEASE_TIME_MS / LOOP_DELAY_MS;
                    cntRelease--;
                } else {
                    cntDetection++;
                }
                break;
            case STATE_PHOTO_SENSORS_DETECTION:
            case STATE_PHOTO_SENSORS_DETECTING:
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                elapsed = millis();
#endif
                cntRelease = DETECTION_RELEASE_TIME_MS / LOOP_DELAY_MS;
                cntRelease--;
                break;
            case STATE_PHOTO_SENSORS_DETECTED:
            default:
                break;
        }
    } else {
        // The sensors is undetected.
        if (0 >= cntRelease) {
            switch (flagState) {
                case STATE_PHOTO_SENSORS_DETECTION:
                case STATE_PHOTO_SENSORS_DETECTING:
                    flagState = STATE_PHOTO_SENSORS_DETECTED;
                    break;
                case STATE_PHOTO_SENSORS_DETECTED:
                case STATE_PHOTO_SENSORS_LOST:
                default:
                    break;
            }
        } else {
            cntRelease--;
        }
        cntDetection = 0;
    }

    switch (flagState) {
        case STATE_PHOTO_SENSORS_DETECTION:
#if DEBUG_OUTPUT_FOR_USB_SERIAL
            str_append = " - detect";
#endif
            for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                if (true == flagDetect[i]) {
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                    sprintf(buffer, "%c %d", delimiter, i);
                    delimiter = ',';
                    str_append += buffer;
#endif
                    bitSet(result, i);
                }
                flagDetect_previous[i] = flagDetect[i];
            }
#if DEBUG_OUTPUT_FOR_USB_SERIAL
            str_append += " ]\n";
#endif
            if (0 == result) {
                result = STATE_PHOTO_SENSORS_UNKNOWN;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                SerialUSB.write(" - detect[lost]\n");
#endif
            } else {
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                SerialUSB.write(str_append.c_str());
#endif
            }
            flagState = STATE_PHOTO_SENSORS_DETECTING;
            break;
        case STATE_PHOTO_SENSORS_DETECTING:
            flagDone = false;
            for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                if (flagDetect_previous[i] != flagDetect[i]) {
                    flagDone = true;
                }
                flagDetect_previous[i] = flagDetect[i];
                if (true == flagDetect[i]) {
                    bitSet(result, i);
                }
            }
#if DEBUG_OUTPUT_FOR_USB_SERIAL
            if (true == flagDone) {
                str_append = " - detect";
                for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                    if (true == flagDetect[i]) {
                        sprintf(buffer, "%c %d", delimiter, i);
                        delimiter = ',';
                        str_append += buffer;
                    }
                }
                str_append += " ]\n";
            }
#endif
            if (0 == result) {
                result = STATE_PHOTO_SENSORS_UNKNOWN;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                SerialUSB.write(" - detect[lost]\n");
#endif
            } else {
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                SerialUSB.write(str_append.c_str());
#endif
            }
            break;
        case STATE_PHOTO_SENSORS_DETECTED:
#if DEBUG_OUTPUT_FOR_USB_SERIAL
            sprintf(buffer, " - lost:%04d ms\n", (int)(millis() - elapsed));
            SerialUSB.write(buffer);
#else
#endif
            flagState = STATE_PHOTO_SENSORS_LOST;
            result    = 0;
            break;
        case STATE_PHOTO_SENSORS_LOST:
        default:
            result = 0;
            break;
    }

    *mode = result;
    return flagState;
}
