/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-12
 *
 * @copyright Copyright (c) 2022
 *
 */

//#include "setting.h"
#include "__private_setting.h"

#include <HTTPClient.h>
#include <M5Stack.h>
#include <VL53L0X.h>
#include <WiFi.h>
#include <Wire.h>

VL53L0X sensor;
HTTPClient http;

const char ssid[]            = SETTING_WIFI_SSID;
const char pass[]            = SETTING_WIFI_PASS;
const char endpoint[]        = SETTING_URL_ENDPOINT;
static int distance_previous = 0;

enum TOP_STATUE
{
    TOF_DOOR_UNKNOW,
    TOF_DOOR_CLOSE,
    TOF_DOOR_OPEN
};

void both_println_lcd(const char *value, uint16_t color = WHITE, bool clear = false)
{
    static int line = 0;
    if ((11 < line) || (true == clear)) {
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.clear();
        char str[150];
        sprintf(str, " IP address =\n    %s", WiFi.localIP().toString().c_str());
        M5.Lcd.setTextColor(GREEN, BLACK);
        M5.Lcd.println(str);
        Serial.println(str);
        line = 2;
    }
    M5.Lcd.setTextColor(color, BLACK);
    M5.Lcd.println(value);
    Serial.println(value);
    line++;
}

void post_top(int flag, int distance)
{
    char str[150];
    HTTPClient http;
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");
    sprintf(str, SETTING_URL_ENDPOINT_KEY, flag, distance);
    int httpCode = http.POST(str);

    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        sprintf(str, "[HTTP] POST... code: %d", httpCode);
        both_println_lcd(str, BLUE);
        // file found at server
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
        sprintf(str, "[HTTP] POST... failed, error: %s", http.errorToString(httpCode).c_str());
        both_println_lcd(str);
    }

    http.end();
}

void setup()
{
    char str[150];
    M5.begin();
    M5.Power.begin();

    Wire.begin();
    sensor.init();
    sensor.setTimeout(500);

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);

    WiFi.begin(ssid, pass);
    both_println_lcd("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
        Serial.print(".");
    }
    both_println_lcd("");

    both_println_lcd("WiFi connected");
    sprintf(str, " IP address =\n    %s", WiFi.localIP().toString().c_str());
    both_println_lcd(str, GREEN);
    distance_previous = sensor.readRangeSingleMillimeters();
}

void loop()
{
    int sleep_time  = SETTING_LOOP_TIME_NORMAL;
    const int range = SETTING_TOF_DETECT_RANG;
    if (WiFi.status() != WL_CONNECTED) {
        both_println_lcd("WiFi disconnected", RED);
        WiFi.reconnect();
        if (WiFi.status() != WL_CONNECTED) {
            sleep_time = SETTING_LOOP_TIME_WIFI_CONNECTED;
        } else {
            both_println_lcd("WiFi connected", GREEN);
        }
    } else {
        int flag     = TOF_DOOR_UNKNOW;
        int distance = sensor.readRangeSingleMillimeters();
        if (0 != distance) {
            if (distance < (distance_previous - range)) {
                flag = TOF_DOOR_CLOSE;
            } else if ((distance_previous + range) < distance) {
                flag = TOF_DOOR_OPEN;
            }
            if (TOF_DOOR_UNKNOW != flag) {
                char str[150];
                switch (flag) {
                    case TOF_DOOR_CLOSE:
                        sprintf(str, "[CLOS] %4d mm <- %4d mm", distance, distance_previous);
                        break;
                    case TOF_DOOR_OPEN:
                        sprintf(str, "[OPEN] %4d mm <- %4d mm", distance, distance_previous);
                        break;

                    default:
                        sprintf(str, "[    ] %4d mm <- %4d mm", distance, distance_previous);
                        break;
                }
                both_println_lcd(str);
                distance_previous = distance;
                if (TOF_DOOR_CLOSE == flag) {
                    post_top(flag, distance);
                    sleep_time = SETTING_LOOP_TIME_SLEEP_DETECT;
                }
            }
        }
    }
    delay(sleep_time);
}