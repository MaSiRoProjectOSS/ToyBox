/**
 * @file settings.hpp
 * @brief
 * @date 2022-06-17
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef SETTINGS_HPP
#define SETTINGS_HPP
/////////////////////////////////////////////////////////////
/**
 * @brief interval on one time loop
 */
#ifndef LOOP_DELAY_MS
#define LOOP_DELAY_MS 100
#endif

/**
 * @brief Output debug messages
 */
#ifndef DEBUG_OUTPUT_FOR_USB_SERIAL
#define DEBUG_OUTPUT_FOR_USB_SERIAL 0
#endif

/**
   @brief Operates after detecting the specified time
*/
#ifndef DETECTION_WAITING_TIME_MS
#define DETECTION_WAITING_TIME_MS 500
#endif
/**
   @brief Drop the flag after the specified time
*/
#ifndef DETECTION_RELEASE_TIME_MS
#define DETECTION_RELEASE_TIME_MS 500
#endif

/**
 * @brief default text size
 */
#ifndef BUFFER_TEXT_SIZE
#define BUFFER_TEXT_SIZE 512
#endif
/////////////////////////////////////////////////////////////
#endif
