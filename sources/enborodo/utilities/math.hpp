#pragma once

#include <cmath>

#include <concepts>
#include <stdexcept>

namespace en
{

template <std::floating_point T>
constexpr T wrap(T value, T min, T max)
{
    if (max <= min)
        throw std::invalid_argument("max must be greater than min");

    const auto range = max - min;
    value = std::fmod(value - min, range);
    return value < 0 ? value + range + min : value + min;
}

}
