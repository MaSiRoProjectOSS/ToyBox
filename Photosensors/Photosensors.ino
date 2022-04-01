/**
   @file Photosensors.ino
   @brief Detected by a photosensors and notified via BLE.
   @date 2022-03-30

   @copyright Copyright (c) MaSiRo Project. 2022-.
                 MaSiRo Project.
*/

////////////////////////////////////////////////////
// SETTING
////////////////////////////////////////////////////
#define LED_LIGHTING_ON_BOARD 1

#define DETECTION_ENABLE_01 1
#define DETECTION_ENABLE_02 1
#define DETECTION_ENABLE_03 1
#define DETECTION_ENABLE_04 1
#define DETECTION_ENABLE_05 1
const uint8_t PIN_OUTPUT_STATUS = LOW;

/**
   @brief Operates after detecting the specified time
*/
const int DETECTION_WAITING_TIME_MS = 1000;
/**
   @brief Drop the flag after the specified time
*/
const int FLAG_RELEASE_TIME_MS = 3000;
////////////////////////////////////////////////////
// CONFIGURATION
////////////////////////////////////////////////////
const int DigitalAnalogPin_NUM = 5;
const int DigitalAnalogPin_1   = 0;
const int DigitalAnalogPin_2   = 1;
const int DigitalAnalogPin_3   = 2;
const int DigitalAnalogPin_4   = 3;
const int DigitalAnalogPin_5   = 4;

//#define DEBUG_OUTPUT
#define RESULT_SENSER_UNKNOWN 128
const int LOOP_DELAY_MS      = 100;
const unsigned int BAUD_RATE = 115200;

// ==================================================== //
////////////////////////////////////////////////////
// enum
////////////////////////////////////////////////////
typedef enum
{
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
#endif
    pinMode(DigitalAnalogPin_1, INPUT);
    pinMode(DigitalAnalogPin_2, INPUT);
    pinMode(DigitalAnalogPin_3, INPUT);
    pinMode(DigitalAnalogPin_4, INPUT);
    pinMode(DigitalAnalogPin_5, INPUT);
}
/**
   @brief Set the up serial object
*/
void setup_serial()
{
    SerialUSB.begin(BAUD_RATE);
    int baud = SerialUSB.baud();
#if false
    // Wait until connected
    do {
    } while (!SerialUSB);
#endif
    Serial1.begin(baud);
    do {
    } while (!Serial1);
    old_baud = SerialUSB.baud();
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
}

/**
 * @brief Detect changes when  digital-in changes at one-second intervals.
 *
 * @return int  The sensor number detected is expressed in bits.
 *              If it is lost, return 'RESULT_SENSER_UNKNOWN'.
 */
int loop_pin()
{
    static STATE_PHOTOSENSORS flagState            = STATE_PHOTOSENSORS_LOST;
    static int cntDetection                        = 0;
    static int cntRelese                           = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
    int result                                     = 0;
    bool flagDetect[DigitalAnalogPin_NUM]          = { false };
    bool flagDetect_previous[DigitalAnalogPin_NUM] = { false };
    bool flagDone                                  = false;
#ifdef DEBUG_OUTPUT
    char buffer[150];
    char delimiter               = '[';
    static unsigned long elapsed = 0;
#endif

#if DETECTION_ENABLE_01
    int buttonState_1 = digitalRead(DigitalAnalogPin_1);
    if (PIN_OUTPUT_STATUS == buttonState_1) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write("buttonState_1\r\n");
#endif
        flagDetect[0] = true;
    }
#endif
#if DETECTION_ENABLE_02
    int buttonState_2 = digitalRead(DigitalAnalogPin_2);
    if (PIN_OUTPUT_STATUS == buttonState_2) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write("buttonState_2\r\n");
#endif
        flagDetect[1] = true;
    }
#endif
#if DETECTION_ENABLE_03
    int buttonState_3 = digitalRead(DigitalAnalogPin_3);
    if (PIN_OUTPUT_STATUS == buttonState_3) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write("buttonState_3\r\n");
#endif
        flagDetect[2] = true;
    }
#endif
#if DETECTION_ENABLE_04
    int buttonState_4 = digitalRead(DigitalAnalogPin_4);
    if (PIN_OUTPUT_STATUS == buttonState_4) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write("buttonState_4\r\n");
#endif
        flagDetect[3] = true;
    }
#endif
#if DETECTION_ENABLE_05
    int buttonState_5 = digitalRead(DigitalAnalogPin_5);
    if (PIN_OUTPUT_STATUS == buttonState_5) {
#ifdef DEBUG_OUTPUT
        SerialUSB.write("buttonState_5\r\n");
#endif
        flagDetect[4] = true;
    }
#endif
    for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
        if (true == flagDetect[i]) {
            flagDone = true;
        }
    }

    if ((true == flagDone)) {
        switch (flagState) {
            case STATE_PHOTOSENSORS_LOST:
                if ((DETECTION_WAITING_TIME_MS / LOOP_DELAY_MS) <= cntDetection) {
                    flagState = STATE_PHOTOSENSORS_DETECTION;
#ifdef DEBUG_OUTPUT
                    elapsed = millis();
#else
                    SerialUSB.write("detect\r\n");
#endif
                    cntRelese = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
                    cntRelese--;
                } else {
                    cntDetection++;
                }
                break;
            case STATE_PHOTOSENSORS_DETECTION:
            case STATE_PHOTOSENSORS_DETECTING:
#ifdef DEBUG_OUTPUT
                elapsed = millis();
#endif
                cntRelese = FLAG_RELEASE_TIME_MS / LOOP_DELAY_MS;
                cntRelese--;
                break;
            case STATE_PHOTOSENSORS_DETECTED:
            default:
                break;
        }
    } else {
        if (0 >= cntRelese) {
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
            cntRelese--;
        }
        cntDetection = 0;
    }

    switch (flagState) {
        case STATE_PHOTOSENSORS_DETECTION:
#if LED_LIGHTING_ON_BOARD == 1
            digitalWrite(PIN_LED, LOW); // turn LED on
#ifdef DEBUG_OUTPUT
            SerialUSB.write("   turn LED on\r\n");
#endif
#endif
#ifdef DEBUG_OUTPUT
            sprintf(buffer, "detect");
#endif
            for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                if (true == flagDetect[i]) {
#ifdef DEBUG_OUTPUT
                    sprintf(buffer, "%s%c %d", buffer, delimiter, i);
                    delimiter = ',';
#endif
                    bitSet(result, i);
                }
                flagDetect_previous[i] = flagDetect[i];
            }
#ifdef DEBUG_OUTPUT
            sprintf(buffer, "%s ]\r\n", buffer);
#endif
            if (0 == result) {
                result = RESULT_SENSER_UNKNOWN;
#ifdef DEBUG_OUTPUT
                SerialUSB.write("detect[lost]\r\n");
#endif
            } else {
#ifdef DEBUG_OUTPUT
                SerialUSB.write(buffer);
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
                sprintf(buffer, "detect");
                for (int i = 0; i < DigitalAnalogPin_NUM; i++) {
                    if (true == flagDetect[i]) {
                        sprintf(buffer, "%s%c %d", buffer, delimiter, i);
                        delimiter = ',';
                    }
                }
                sprintf(buffer, "%s ]\r\n", buffer);
            }
#endif
            if (0 == result) {
                result = RESULT_SENSER_UNKNOWN;
#ifdef DEBUG_OUTPUT
                SerialUSB.write("detect[lost]\r\n");
#endif
            } else {
#ifdef DEBUG_OUTPUT
                SerialUSB.write(buffer);
#endif
            }
            break;
        case STATE_PHOTOSENSORS_DETECTED:
#if LED_LIGHTING_ON_BOARD == 1
            digitalWrite(PIN_LED, HIGH); // turn LED off
#ifdef DEBUG_OUTPUT
            SerialUSB.write("   turn LED off\r\n");
#endif
#endif
#ifdef DEBUG_OUTPUT
            sprintf(buffer, "lost:%d ms\r\n", millis() - elapsed);
            SerialUSB.write(buffer);
#else
            SerialUSB.write("lost\r\n");
#endif
            flagState = STATE_PHOTOSENSORS_LOST;
            result    = 0;
            break;
        case STATE_PHOTOSENSORS_LOST:
        default:
            result = 0;
            break;
    }

    return result;
}

/**
   @brief
*/
void loop_ble() {}
// ==================================================== //

void setup()
{
    setup_pin();
    setup_serial();
    setup_ble();
}

void loop()
{
    loop_serial();
    int result = loop_pin();
#ifdef DEBUG_OUTPUT
    if (0 != result) {
        char buffer[100];
        sprintf(buffer, "RESULT[%d]\r\n", result);
        SerialUSB.write(buffer);
    }
#endif
    loop_ble();

    // delay
    delay(LOOP_DELAY_MS);
}
