/**
 * @file main.c
   @brief Detected by a photo sensors.
 * @date 2022-06-17
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#include "devices/photo_sensors.hpp"
#include "devices/rn4020_serial.hpp"
#include "devices/ssd1306.hpp"
#include "devices/usb_serial.hpp"
#include "settings.hpp"

#include <Arduino.h>

////////////////////////////////////////////////////
// SETTING
////////////////////////////////////////////////////
/**
 * @brief flat that led lighting on board
 */
#ifndef LED_LIGHTING_ON_BOARD
#define LED_LIGHTING_ON_BOARD 0
#endif

#define USB_WAIT_UNTIL_CONNECTED 0
#define USB_USING                1

////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////

// ==================================================== //
////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////

// ==================================================== //
void setup()
{
#if LED_LIGHTING_ON_BOARD == 1
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH); // turn LED off
#endif
#if USB_USING
#if USB_WAIT_UNTIL_CONNECTED
    // Wait until connected
    do {
    } while (!SerialUSB);
    char buffer[100];
    sprintf(buffer, "=======\nSTART : PhotoSensors\n=======\n");
    SerialUSB.write(buffer);
#endif
#endif
    setup_photo_sensors();
    setup_usb_serial();
    setup_rn4020_serial();
    setup_ssd1306();
}

void loop()
{
    loop_ssd1306();
    static int previous_mode   = -1;
    static int previous_result = -1;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
    static char buffer[100] = "\0";
#endif
    static int mode;
    int result = get_photo_sensors(&mode);
    if ((previous_mode != mode) || (previous_result != result)) {
        switch (result) {
            case STATE_PHOTO_SENSORS_DETECTION:
            case STATE_PHOTO_SENSORS_DETECTING:
                switch (mode) {
                    case 1:
                        SerialUSB.write("<\n");
                        break;
                    case 2:
                        SerialUSB.write(">\n");
                        break;
                    case 3:
                        SerialUSB.write("|\n");
                        break;
                    default:
                        break;
                }
                if (previous_result != result) {
                    //SerialUSB.write("DETECTED\n");
#if LED_LIGHTING_ON_BOARD == 1
                    digitalWrite(PIN_LED, LOW); // turn LED on
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                    SerialUSB.write(" - turn LED on\n");
#endif
#endif
                }
                break;
            case STATE_PHOTO_SENSORS_LOST:
                SerialUSB.write("-\n");
                //SerialUSB.write("LOST\n");
            case STATE_PHOTO_SENSORS_UNKNOWN:
            default:
#if LED_LIGHTING_ON_BOARD == 1
                digitalWrite(PIN_LED, HIGH); // turn LED off
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                SerialUSB.write(" - turn LED off\n");
#endif
#endif
                break;
        }
#if DEBUG_OUTPUT_FOR_USB_SERIAL
        sprintf(buffer, "RESULT[%d,%d]\n", result, mode);
        SerialUSB.write(buffer);
#endif
        previous_mode   = mode;
        previous_result = result;
    }

    // delay
    delay(LOOP_DELAY_MS);
}
