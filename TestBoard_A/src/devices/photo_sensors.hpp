/**
 * @file photo_sensors.hpp
 * @brief photo_sensors
 * @date 2022-06-17
 *
 * @copyright Copyright (c) MaSiRo Project. 2022-.
 *               MaSiRo Project.
 *
 */
#ifndef PHOTO_SENSORS_HPP
#define PHOTO_SENSORS_HPP

////////////////////////////////////////////////////
// enum
////////////////////////////////////////////////////
typedef enum
{
    STATE_PHOTO_SENSORS_UNKNOWN,
    STATE_PHOTO_SENSORS_DETECTION,
    STATE_PHOTO_SENSORS_DETECTING,
    STATE_PHOTO_SENSORS_DETECTED,
    STATE_PHOTO_SENSORS_LOST,
} STATE_PHOTO_SENSORS;
// ==================================================== //

void setup_photo_sensors();
int get_photo_sensors(int *mode);
#endif
