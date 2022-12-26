/**
 * @file xiao_expansion_imu.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_IMU_HPP
#define XIAO_EXPANSION_IMU_HPP

#include "LSM6DS3.h"
#include "common/common_function.hpp"
#include "common/vector3.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
#ifndef XIAO_IMU_UNKNOWN_TEMP
#define XIAO_IMU_UNKNOWN_TEMP (-999)
#endif
#ifndef EXAMPLE_LIBRARY_XIAO_IMU
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_IMU 1
#else
#define EXAMPLE_LIBRARY_XIAO_IMU 0
#endif
#endif

class XIAOImu {
public:
    XIAOImu();
    ~XIAOImu();

public:
    bool setup(LSM6DS3 *imu);
    bool loop(void);

public:
    Vector3 get_accel();
    Vector3 get_gyro();
    float get_TempC();
    bool update(void);

private:
    Vector3 accel;
    Vector3 gyro;
    float temp;
    bool _set_accel();
    bool _set_gyro();
    bool _set_TempC();

private:
    LSM6DS3 *com_imu;
    const float unknown_temp = XIAO_IMU_UNKNOWN_TEMP;

    const unsigned long READ_SPAN_MS = (1000);
    bool initialize                  = false;
};
} // namespace Parts
} // namespace XIAO

#endif
