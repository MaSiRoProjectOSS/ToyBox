/**
   @file Photosensors.ino
   @brief Detected by a photosensors and notified via BLE.
   @date 2022-03-30

   @copyright Copyright (c) MaSiRo Project. 2022-.
                 MaSiRo Project.
*/
#include <Arduino.h>

//#define DEBUG_OUTPUT

////////////////////////////////////////////////////
// SETTING
////////////////////////////////////////////////////
#define LED_LIGHTING_ON_BOARD 1

#define DETECTION_ENABLE_01 0
#define DETECTION_ENABLE_02 0
#define DETECTION_ENABLE_03 0
#define DETECTION_ENABLE_04 1
#define DETECTION_ENABLE_05 1
const uint8_t PIN_OUTPUT_STATUS = LOW;
#define USB_WAIT_UNTIL_CONNECTED    0
#define USB_USING                   1
#define SERIAL_WAIT_UNTIL_CONNECTED 0
#define SERIAL_USING                0

/**
   @brief Operates after detecting the specified time
*/
const int DETECTION_WAITING_TIME_MS = 500;
/**
   @brief Drop the flag after the specified time
*/
const int FLAG_RELEASE_TIME_MS = 1500;
////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////
const int DigitalAnalogPin_NUM = 5;
#if DETECTION_ENABLE_01
const int DigitalAnalogPin_1 = 0;
#endif
#if DETECTION_ENABLE_02
const int DigitalAnalogPin_2 = 1;
#endif
#if DETECTION_ENABLE_03
const int DigitalAnalogPin_3 = 2;
#endif
#if DETECTION_ENABLE_04
const int DigitalAnalogPin_4 = 4;
#endif
#if DETECTION_ENABLE_05
const int DigitalAnalogPin_5 = 5;
#endif

const int LOOP_DELAY_MS      = 100;
const unsigned int BAUD_RATE = 115200;

// ==================================================== //
////////////////////////////////////////////////////
// enum
////////////////////////////////////////////////////
typedef enum
{
    STATE_PHOTOSENSORS_UNKNOWN,
    STATE_PHOTOSENSORS_DETECTION,
    STATE_PHOTOSENSORS_DETECTING,
    STATE_PHOTOSENSORS_DETECTED,
    STATE_PHOTOSENSORS_LOST,
} STATE_PHOTOSENSORS;
////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////
static int old_baud = 0;

// ==================================================== //
////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////
/**
   @brief Set the up pin object
*/
void setup_pin()
{
#if LED_LIGHTING_ON_BOARD == 1
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH); // turn LED off
#endif
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
   @brief Set the up serial object
*/
void setup_serial()
{
#if USB_USING
    SerialUSB.begin(BAUD_RATE);
#if USB_WAIT_UNTIL_CONNECTED
    // Wait until connected
    do {
    } while (!SerialUSB);
#endif
    old_baud = SerialUSB.baud();
#endif
#if SERIAL_USING
#if SERIAL_WAIT_UNTIL_CONNECTED
    int baud = SerialUSB.baud();
    Serial1.begin(baud);
    do {
    } while (!Serial1);
#endif
#endif
}
/**
   @brief Set the up ble object
*/
void setup_ble() {}
// ==================================================== //
////////////////////////////////////////////////////
// loop
////////////////////////////////////////////////////
/**
   @brief Reconnect if there is a baud rate change./Serial communication intermediary.
*/
void loop_serial()
{
    ////////////////////////////////////////////////////
    // Serial
    ////////////////////////////////////////////////////
#if USB_USING
#if SERIAL_USING
    if (!Serial1) {
        int baud = SerialUSB.baud();
        if (baud != old_baud) {
            Serial1.begin(baud);
            do {
            } while (!Serial1);
            old_baud = baud;
        }
    }
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        SerialUSB.write(c);
    }
    while (SerialUSB.available() > 0) {
        char c = SerialUSB.read();
        Serial1.write(c);
    }
#endif
#endif
}

/**
 * @brief Get the pin state object
 *
 * @param pin_value
 * @param buffer
 * @return true
 * @return false
 */
bool get_pin_state(uint32_t pin_value, String buffer = "")
{
    bool result     = false;
    int buttonState = digitalRead(pin_value);
    if (PIN_OUTPUT_STATUS == buttonState) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write((buffer + "\n").c_str());
#endif
        result = true;
    }
    return result;
}

/**
 * @brief Detect changes when  digital-in changes at one-second intervals.
 *
 * @return int  The sensor number detected is expressed in bits.
 *              If it is lost, return 'STATE_PHOTOSENSORS_UNKNOWN'.
 */
int loop_pin(int *mode)
{
    static STATE_PHOTOSENSORS flagState                   = STATE_PHOTOSENSORS_LOST;
    static int cntDetection                               = 0;
    static int cntRelease                                 = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
    static bool flagDetect_previous[DigitalAnalogPin_NUM] = { false };
    bool flagDetect[DigitalAnalogPin_NUM]                 = { false };
    int result                                            = 0;
    bool flagDone                                         = false;
#ifdef DEBUG_OUTPUT
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
            case STATE_PHOTOSENSORS_LOST:
                if ((DETECTION_WAITING_TIME_MS / LOOP_DELAY_MS) <= cntDetection) {
                    flagState = STATE_PHOTOSENSORS_DETECTION;
#ifdef DEBUG_OUTPUT
                    elapsed = millis();
#else
#endif
                    cntRelease = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
                    cntRelease--;
                } else {
                    cntDetection++;
                }
                break;
            case STATE_PHOTOSENSORS_DETECTION:
            case STATE_PHOTOSENSORS_DETECTING:
#ifdef DEBUG_OUTPUT
                elapsed = millis();
#endif
                cntRelease = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
                cntRelease--;
                break;
            case STATE_PHOTOSENSORS_DETECTED:
            default:
                break;
        }
    } else {
        // The sensors is undetected.
        if (0 >= cntRelease) {
            switch (flagState) {
                case STATE_PHOTOSENSORS_DETECTION:
                case STATE_PHOTOSENSORS_DETECTING:
                    flagState = STATE_PHOTOSENSORS_DETECTED;
                    break;
                case STATE_PHOTOSENSORS_DETECTED:
                case STATE_PHOTOSENSORS_LOST:
                default:
                    break;
            }
        } else {
            cntRelease--;
        }
        cntDetection = 0;
    }

    switch (flagState) {
        case STATE_PHOTOSENSORS_DETECTION:
#if LED_LIGHTING_ON_BOARD == 1
            digitalWrite(PIN_LED, LOW); // turn LED on
#ifdef DEBUG_OUTPUT
            SerialUSB.write(" - turn LED on\n");
#endif
#endif
#ifdef DEBUG_OUTPUT
            str_append = " - detect";
#endif
            for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                if (true == flagDetect[i]) {
#ifdef DEBUG_OUTPUT
                    sprintf(buffer, "%c %d", delimiter, i);
                    delimiter = ',';
                    str_append += buffer;
#endif
                    bitSet(result, i);
                }
                flagDetect_previous[i] = flagDetect[i];
            }
#ifdef DEBUG_OUTPUT
            str_append += " ]\n";
#endif
            if (0 == result) {
                result = STATE_PHOTOSENSORS_UNKNOWN;
#ifdef DEBUG_OUTPUT
                SerialUSB.write(" - detect[lost]\n");
#endif
            } else {
#ifdef DEBUG_OUTPUT
                SerialUSB.write(str_append.c_str());
#endif
            }
            flagState = STATE_PHOTOSENSORS_DETECTING;
            break;
        case STATE_PHOTOSENSORS_DETECTING:
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
#ifdef DEBUG_OUTPUT
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
                result = STATE_PHOTOSENSORS_UNKNOWN;
#ifdef DEBUG_OUTPUT
                SerialUSB.write(" - detect[lost]\n");
#endif
            } else {
#ifdef DEBUG_OUTPUT
                SerialUSB.write(str_append.c_str());
#endif
            }
            break;
        case STATE_PHOTOSENSORS_DETECTED:
#if LED_LIGHTING_ON_BOARD == 1
            digitalWrite(PIN_LED, HIGH); // turn LED off
#ifdef DEBUG_OUTPUT
            SerialUSB.write(" - turn LED off\n");
#endif
#endif
#ifdef DEBUG_OUTPUT
            sprintf(buffer, " - lost:%04d ms\n", (int)(millis() - elapsed));
            SerialUSB.write(buffer);
#else
#endif
            flagState = STATE_PHOTOSENSORS_LOST;
            result    = 0;
            break;
        case STATE_PHOTOSENSORS_LOST:
        default:
            result = 0;
            break;
    }

    *mode = result;
    return flagState;
}

/**
   @brief
*/
void loop_ble() {}
// ==================================================== //

void setup()
{
    char buffer[100];
    sprintf(buffer, "=======\nSTART : Photosensors\n=======\n");
    SerialUSB.write(buffer);
    setup_pin();
    setup_serial();
    setup_ble();
}

void loop()
{
    static int previous_mode   = -1;
    static int previous_result = -1;
#ifdef DEBUG_OUTPUT
    static char buffer[100] = "\0";
#endif
    static int mode;
    loop_serial();
    int result = loop_pin(&mode);
    if ((previous_mode != mode) || (previous_result != result)) {
        switch (result) {
            case STATE_PHOTOSENSORS_DETECTION:
            case STATE_PHOTOSENSORS_DETECTING:
                switch (mode) {
                    case 16:
                        SerialUSB.write("<\n");
                        break;
                    case 24:
                        SerialUSB.write("|\n");
                        break;
                    case 8:
                        SerialUSB.write(">\n");
                        break;
                    default:
                        break;
                }
                if (previous_result != result) {
                    //SerialUSB.write("DETECTED\n");
                }
                break;
            case STATE_PHOTOSENSORS_LOST:
                SerialUSB.write("-\n");
                //SerialUSB.write("LOST\n");
                break;
            case STATE_PHOTOSENSORS_UNKNOWN:
            default:
                break;
        }
#ifdef DEBUG_OUTPUT
        sprintf(buffer, "RESULT[%d,%d]\n", result, mode);
        SerialUSB.write(buffer);
#endif
        previous_mode   = mode;
        previous_result = result;
    }
    loop_ble();

    // delay
    delay(LOOP_DELAY_MS);
}
