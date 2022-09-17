/**
 * @file setting.h
 * @brief
 * @version 0.1
 * @date 2022-09-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SETTING_H
#define SETTING_H

#ifndef SETTING_WIFI_SSID
/**
 * @brief Specify Wifi SSID
 *
 */
#define SETTING_WIFI_SSID "(wifi ssid)"
#endif
#ifndef SETTING_WIFI_PASS
/**
 * @brief Specify Wifi SSID password
 *
 */
#define SETTING_WIFI_PASS "(wifi password)"
#endif
#ifndef SETTING_URL_ENDPOINT
/**
 * @brief Specify the URL of the connected endpoint.
 *
 */
#define SETTING_URL_ENDPOINT "(URL : http://---.com/---?set_data.html)"
#endif
#ifndef SETTING_URL_ENDPOINT_KEY
/**
 * @brief Specify Key (json format)
 * @example * "{\"flag\" : %d, \"distance\" : %d }"
 */
#define SETTING_URL_ENDPOINT_KEY "{\"flag\" : %d, \"distance\" : %d }"
#endif

#ifndef SETTING_TOF_DETECT_RANG
/**
 * @brief Responsive detection range (unit: mm)
 *
 */
#define SETTING_TOF_DETECT_RANG 500
#endif

#ifndef SETTING_LOOP_TIME_NORMAL
/**
 * @brief Specify the interval to detect
 *
 */
#define SETTING_LOOP_TIME_NORMAL 250
#endif

#ifndef SETTING_LOOP_TIME_SLEEP_DETECT
/**
 * @brief Specify no response time after detection (unit: mm)
 *
 */
#define SETTING_LOOP_TIME_SLEEP_DETECT 2000
#endif
#ifndef SETTING_LOOP_TIME_WIFI_CONNECTED
/**
 * @brief Specify the retry waiting time after Wifi disconnection.
 *
 */
#define SETTING_LOOP_TIME_WIFI_CONNECTED 10000
#endif
#endif