/**
 * @file xiao_expansion_rtc.hpp
 * @author Akari (masiro.to.akari@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef XIAO_EXPANSION_RTC_HPP
#define XIAO_EXPANSION_RTC_HPP

#include "common/common_function.hpp"

namespace XIAO
{
namespace Parts
{
#ifndef EXAMPLE_LIBRARY_XIAO_RTC
#if EXAMPLE_PROGRAM
#define EXAMPLE_LIBRARY_XIAO_RTC 1
#else
#define EXAMPLE_LIBRARY_XIAO_RTC 0
#endif
#endif

class XIAORtc {
public:
    XIAORtc();
    ~XIAORtc();

public:
    bool setup(void);
    bool loop(void);

private:
    const unsigned long READ_SPAN_MS = (1 * 1000);
    bool initialize                  = false;
};
} // namespace Parts
} // namespace XIAO

#endif
