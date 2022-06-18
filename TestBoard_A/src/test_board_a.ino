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
#include "devices/serial_on_board.hpp"
#include "devices/serial_usb.hpp"
#include "devices/ssd1306.hpp"
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
////////////////////////////////////////////////////
// PRIVATE FUNCTION
////////////////////////////////////////////////////
static void send_text(const char value[])
{
    serial_usb_write(value);
    serial_on_board_write(value);
}

// ==================================================== //
////////////////////////////////////////////////////
// Arduino FUNCTION
////////////////////////////////////////////////////

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
    send_text(buffer);
#endif
#endif
    setup_photo_sensors();
    setup_serial_usb();
    setup_serial_on_board();
    setup_ssd1306();
}

void loop()
{
    loop_ssd1306();
    static char *read_data[BUFFER_TEXT_SIZE];
    static int previous_mode   = -1;
    static int previous_result = -1;
#if DEBUG_OUTPUT_FOR_USB_SERIAL
    static char buffer[100] = "\0";
#endif
    if (true == serial_usb_read(read_data)) {
        //
        serial_on_board_write(*read_data);
    }
    if (true == serial_on_board_read(read_data)) {
        //
        serial_usb_write(*read_data);
    }

    // photo_sensors
    static int mode;
    int result = get_photo_sensors(&mode);
    if ((previous_mode != mode) || (previous_result != result)) {
        switch (result) {
            case STATE_PHOTO_SENSORS_DETECTION:
            case STATE_PHOTO_SENSORS_DETECTING:
                switch (mode) {
                    case 1:
                        send_text("<\n");
                        break;
                    case 2:
                        send_text(">\n");
                        break;
                    case 3:
                        send_text("|\n");
                        break;
                    default:
                        break;
                }
                if (previous_result != result) {
                    //send_text("DETECTED\n");
#if LED_LIGHTING_ON_BOARD == 1
                    digitalWrite(PIN_LED, LOW); // turn LED on
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                    send_text(" - turn LED on\n");
#endif
#endif
                }
                break;
            case STATE_PHOTO_SENSORS_LOST:
                send_text("-\n");
                //send_text("LOST\n");
            case STATE_PHOTO_SENSORS_UNKNOWN:
            default:
#if LED_LIGHTING_ON_BOARD == 1
                digitalWrite(PIN_LED, HIGH); // turn LED off
#if DEBUG_OUTPUT_FOR_USB_SERIAL
                send_text(" - turn LED off\n");
#endif
#endif
                break;
        }
#if DEBUG_OUTPUT_FOR_USB_SERIAL
        sprintf(buffer, "RESULT[%d,%d]\n", result, mode);
        send_text(buffer);
#endif
        previous_mode   = mode;
        previous_result = result;
    }

    // delay
    delay(LOOP_DELAY_MS);
}
