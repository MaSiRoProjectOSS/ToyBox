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

#define DITECTION_ENABLE_01 1
#define DITECTION_ENABLE_02 0
#define DITECTION_ENABLE_03 1
#define DITECTION_ENABLE_04 0
#define DITECTION_ENABLE_05 1

////////////////////////////////////////////////////
// CONFIG
////////////////////////////////////////////////////
const int DigitalAnalogPin_1 = 0;
const int DigitalAnalogPin_2 = 1;
const int DigitalAnalogPin_3 = 2;
const int DigitalAnalogPin_4 = 3;
const int DigitalAnalogPin_5 = 4;
const int LOOP_DELAY_MS = 100;
const unsigned int BAUD_RATE = 115200;
////////////////////////////////////////////////////
// CONFIG
////////////////////////////////////////////////////
typedef enum {
  STATE_DITECTION_DETECTION,
  STATE_DITECTION_DETECTING,
  STATE_DITECTION_DETECTED,
  STATE_DITECTION_LOST,
} STATE_DITECTION;

// ==================================================== //
////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////
/**
   @brief Set the up pin object
*/
void setup_pin() {
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
void setup_serial() {
  SerialUSB.begin(BAUD_RATE);
  int baud = SerialUSB.baud();
#if false
  do {
  } while (!SerialUSB);
#endif
  Serial1.begin(baud);
  do {
  } while (!Serial1);
}
/**
   @brief Set the up ble object
*/
void setup_ble() {}
// ==================================================== //
////////////////////////////////////////////////////
// loop
////////////////////////////////////////////////////
static int old_baud = 0;
/**
   @brief
*/
void loop_serial() {
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
   @brief
*/
int loop_pin() {
  int result = 0;
  static int cntDetection = 0;
  static STATE_DITECTION flagState = STATE_DITECTION_LOST;
  bool flagDone = false;

  if (cntDetection >= 10) {
#if DITECTION_ENABLE_01
    int buttonState_1 = digitalRead(DigitalAnalogPin_1);
    if (buttonState_1 == LOW) {
      flagDone = true;
    }
#endif
#if DITECTION_ENABLE_02
    int buttonState_2 = digitalRead(DigitalAnalogPin_2);
    if (buttonState_2 == LOW) {
      flagDone = true;
    }
#endif
#if DITECTION_ENABLE_03
    int buttonState_3 = digitalRead(DigitalAnalogPin_3);
    if (buttonState_3 == LOW) {
      flagDone = true;
    }
#endif
#if DITECTION_ENABLE_04
    int buttonState_4 = digitalRead(DigitalAnalogPin_4);
    if (buttonState_4 == LOW) {
      flagDone = true;
    }
#endif
#if DITECTION_ENABLE_05
    int buttonState_5 = digitalRead(DigitalAnalogPin_5);
    if (buttonState_5 == LOW) {
      flagDone = true;
    }
#endif

    if (true == flagDone) {
      if (STATE_DITECTION_LOST == flagState) {
        SerialUSB.write("detection\r\n");
        flagState = STATE_DITECTION_DETECTION;
      }
    } else {
      if (STATE_DITECTION_DETECTING == flagState) {
        flagState = STATE_DITECTION_DETECTED;
      }
    }
    cntDetection = 0;
  } else {
    cntDetection++;
  }

  switch (flagState) {
    case STATE_DITECTION_DETECTION:
#if LED_LIGHTING_ON_BOARD == 1
      digitalWrite(PIN_LED, LOW);  // turn LED on
      SerialUSB.write("   turn LED on\r\n");
#endif
      flagState = STATE_DITECTION_DETECTING;
      result = 1;
      break;
    case STATE_DITECTION_DETECTING:
      result = 1;
      break;
    case STATE_DITECTION_DETECTED:
#if LED_LIGHTING_ON_BOARD == 1
      digitalWrite(PIN_LED, HIGH);  // turn LED off
      SerialUSB.write("   turn LED off\r\n");
#endif
      flagState = STATE_DITECTION_LOST;
      break;
    case STATE_DITECTION_LOST:
      break;
    default:
      break;
  }

  return result;
}

/**
   @brief
*/
void loop_ble() {}
// ==================================================== //

void setup() {
  setup_pin();
  setup_serial();
  setup_ble();
}

void loop() {
  loop_pin();
  loop_serial();
  loop_ble();

  // delay
  delay(LOOP_DELAY_MS);
}
