#pragma once

#include <cstdint>

namespace en
{

struct color
{
    constexpr color() = default;

    explicit constexpr color(uint32_t rgba);

    constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    constexpr color(float r, float g, float b, float a = 1.0f);

    static const color black;
    static const color white;

    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
};

}

#include <enborodo/rendering/color.inl>
