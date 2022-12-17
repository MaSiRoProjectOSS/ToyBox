/**
 * @file vector3.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_COMMON_VECTOR3_HPP
#define XIAO_COMMON_VECTOR3_HPP

namespace XIAO
{
class Vector3 {
public:
    Vector3(float x_axis = 0, float y_axis = 0, float z_axis = 0) : x(x_axis), y(y_axis), z(z_axis) {}
    void Set(float x_axis = 0, float y_axis = 0, float z_axis = 0)
    {
        this->x = x_axis;
        this->y = y_axis;
        this->z = z_axis;
    }

    float x = 0;
    float y = 0;
    float z = 0;
};
} // namespace XIAO

#endif