/**
 * @file xiao_expansion_imu.cpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "parts/xiao_expansion_imu.hpp"

namespace XIAO
{
namespace Parts
{
XIAOImu::XIAOImu() : temp(this->unknown_temp)
{
}
XIAOImu::~XIAOImu()
{
}
bool XIAOImu::setup(LSM6DS3 *imu)
{
    bool result   = true;
    this->com_imu = imu;
    if (0 != com_imu->begin()) {
        result = false;
    }
    this->initialize = result;
    return this->initialize;
}
bool XIAOImu::loop(void)
{
    bool result                        = false;
    static unsigned long previous_time = 0;
    if (true == this->initialize) {
        unsigned long current_time = millis();
        if ((this->READ_SPAN_MS + previous_time) < current_time) {
            previous_time = current_time;
            result        = update();
        }
    }
    return result;
}
bool XIAOImu::update(void)
{
    int result = 0;
    if (true == this->initialize) {
        result += (true == this->_set_accel()) ? 1 : 0;
        result += (true == this->_set_gyro()) ? 1 : 0;
        result += (true == this->_set_TempC()) ? 1 : 0;
    }
    return (3 <= result) ? true : false;
}

bool XIAOImu::_set_accel()
{
    bool result = false;
    if (true == this->initialize) {
        this->accel.Set( //
                com_imu->readFloatAccelX(),
                com_imu->readFloatAccelY(),
                com_imu->readFloatAccelZ());
#if EXAMPLE_LIBRARY_XIAO_IMU
        char buffer[255];
        sprintf(buffer, //
                "XIAOImu :  ax[%9.3f], ay[%9.3f], az[%9.3f]",
                accel.x,
                accel.y,
                accel.z);
        CommonFunction::output_message(false, buffer);
#endif
        result = true;
    }
    return result;
}
bool XIAOImu::_set_gyro()
{
    bool result = false;
    if (true == this->initialize) {
        this->gyro.Set( //
                com_imu->readFloatGyroX(),
                com_imu->readFloatGyroY(),
                com_imu->readFloatGyroZ());
#if EXAMPLE_LIBRARY_XIAO_IMU
        char buffer[255];
        sprintf(buffer, //
                "XIAOImu :  gx[%9.3f], gy[%9.3f], gz[%9.3f]",
                gyro.x,
                gyro.y,
                gyro.z);
        CommonFunction::output_message(false, buffer);
#endif
        result = true;
    }
    return result;
}
bool XIAOImu::_set_TempC()
{
    bool result = false;
    if (true == this->initialize) {
        this->temp = com_imu->readTempC();
#if EXAMPLE_LIBRARY_XIAO_IMU
        char buffer[255];
        sprintf(buffer, //
                "XIAOImu : tmp[%9.3f]",
                temp);
        CommonFunction::output_message(false, buffer);
#endif
        result = true;
    }
    return result;
}

Vector3 XIAOImu::get_accel()
{
    return this->accel;
}
Vector3 XIAOImu::get_gyro()
{
    return this->gyro;
}
float XIAOImu::get_TempC()
{
    return this->temp;
}

} // namespace Parts
} // namespace XIAO
