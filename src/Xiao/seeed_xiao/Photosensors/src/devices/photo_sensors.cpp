/**
 * @file photo_sensors.cpp
 * @brief Detected by a photo sensors.
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
// SOFTWARE SETTINGS
////////////////////////////////////////////////////
const int DigitalAnalogPin_NUM = 5;
/**
 * @brief DETECTION_PIN_NUMBER_1
 */
#if PHOTO_SENSORS_PIN_RANGE_MIN <= DETECTION_PIN_NUMBER_1
#if PHOTO_SENSORS_PIN_RANGE_MAX >= DETECTION_PIN_NUMBER_1
const int DigitalAnalogPin_1 = DETECTION_PIN_NUMBER_1;
#define DETECTION_ENABLE_01 1
#endif
#endif
/**
 * @brief DETECTION_PIN_NUMBER_2
 */
#if PHOTO_SENSORS_PIN_RANGE_MIN <= DETECTION_PIN_NUMBER_2
#if PHOTO_SENSORS_PIN_RANGE_MAX >= DETECTION_PIN_NUMBER_2
const int DigitalAnalogPin_2 = DETECTION_PIN_NUMBER_2;
#define DETECTION_ENABLE_02 1
#endif
#endif
/**
 * @brief DETECTION_PIN_NUMBER_3
 */
#if PHOTO_SENSORS_PIN_RANGE_MIN <= DETECTION_PIN_NUMBER_3
#if PHOTO_SENSORS_PIN_RANGE_MAX >= DETECTION_PIN_NUMBER_3
const int DigitalAnalogPin_3 = DETECTION_PIN_NUMBER_3;
#define DETECTION_ENABLE_03 1
#endif
#endif
/**
 * @brief DETECTION_PIN_NUMBER_4
 */
#if PHOTO_SENSORS_PIN_RANGE_MIN <= DETECTION_PIN_NUMBER_4
#if PHOTO_SENSORS_PIN_RANGE_MAX >= DETECTION_PIN_NUMBER_4
const int DigitalAnalogPin_4 = DETECTION_PIN_NUMBER_4;
#define DETECTION_ENABLE_04 1
#endif
#endif
/**
 * @brief DETECTION_PIN_NUMBER_5
 */
#if PHOTO_SENSORS_PIN_RANGE_MIN <= DETECTION_PIN_NUMBER_5
#if PHOTO_SENSORS_PIN_RANGE_MAX >= DETECTION_PIN_NUMBER_5
const int DigitalAnalogPin_5 = DETECTION_PIN_NUMBER_5;
#define DETECTION_ENABLE_05 1
#endif
#endif

////////////////////////////////////////////////////
// HARDWARE SETTINGS
////////////////////////////////////////////////////
const uint8_t PIN_OUTPUT_STATUS = LOW;

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
static bool get_pin_state(uint32_t pin_value, String buffer = "")
{
    bool result     = false;
    int buttonState = digitalRead(pin_value);
    if (PIN_OUTPUT_STATUS == buttonState) {
#if DEBUG_OUTPUT_FOR_USB_SERIAL
        SerialUSB.write((buffer + "\n").c_str());
#endif
        result = true;
    }
    return result;
}
// ==================================================== //
////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////
void setup_photo_sensors()
{
#if DETECTION_ENABLE_01
    pinMode(DigitalAnalogPin_1, INPUT);
#endif
#if DETECTION_ENABLE_02
    pinMode(DigitalAnalogPin_2, INPUT);
#endif
#if DETECTION_ENABLE_03
    pinMode(DigitalAnalogPin_3, INPUT);
#endif
#if DETECTION_ENABLE_04
    pinMode(DigitalAnalogPin_4, INPUT);
#endif
#if DETECTION_ENABLE_05
    pinMode(DigitalAnalogPin_5, INPUT);
#endif
}

/**
 * @brief Detect changes when  digital-in changes at one-second intervals.
 *
 * @return int  The sensor number detected is expressed in bits.
 *              If it is lost, return 'STATE_PHOTO_SENSORS'.
 */
int get_photo_sensors(int *mode)
{
    static STATE_PHOTO_SENSORS flagState                  = STATE_PHOTO_SENSORS_LOST;
    static int cntDetection                               = 0;
    static int cntRelease                                 = DETECTION_RELEASE_TIME_MS / LOOP_DELAY_MS;
    static bool flagDetect_previous[DigitalAnalogPin_NUM] = { false };
    bool flagDetect[DigitalAnalogPin_NUM]                 = { false };
    int result                                            = 0;
    bool flagDone                                         = false;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
    String str_append = "";
    char buffer[150];
    char delimiter               = '[';
    static unsigned long elapsed = 0;
#endif
    *mode = 0;

#if DETECTION_ENABLE_01
    flagDetect[0] = get_pin_state(DigitalAnalogPin_1, " - buttonState_1");
#endif
#if DETECTION_ENABLE_02
    flagDetect[1] = get_pin_state(DigitalAnalogPin_2, " - buttonState_2");
#endif
#if DETECTION_ENABLE_03
    flagDetect[2] = get_pin_state(DigitalAnalogPin_3, " - buttonState_3");
#endif
#if DETECTION_ENABLE_04
    flagDetect[3] = get_pin_state(DigitalAnalogPin_4, " - buttonState_4");
#endif
#if DETECTION_ENABLE_05
    flagDetect[4] = get_pin_state(DigitalAnalogPin_5, " - buttonState_5");
#endif
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
