/**
 * @file xiao_expansion_user_button.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_USER_BUTTON_HPP
#define XIAO_EXPANSION_USER_BUTTON_HPP

#include "common/common_function.hpp"

#include <Arduino.h>

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_USER_BUTTON
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_USER_BUTTON 1
#else
#define EXAMPLE_LIBRARY_XIAO_USER_BUTTON 0
#endif
#endif

class XIAOUserButton {
public:
    XIAOUserButton();
    ~XIAOUserButton();

public:
    bool setup();

    PinStatus get();

private:
    const pin_size_t PIN = D1;
    bool initialize      = false;

#if EXAMPLE_LIBRARY_XIAO_USER_BUTTON
public:
    bool example();
    const unsigned long READ_SPAN_MS = (2 * 1000);
#endif
};
} // namespace Parts
} // namespace XIAO

#endif
