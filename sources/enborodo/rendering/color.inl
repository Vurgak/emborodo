namespace en
{

constexpr color::color(const uint32_t rgba) :
        r{static_cast<float>((rgba & 0xff000000) >> 24) / 255.0f},
        g{static_cast<float>((rgba & 0x00ff0000) >> 16) / 255.0f},
        b{static_cast<float>((rgba & 0x0000ff00) >> 8) / 255.0f},
        a{static_cast<float>((rgba & 0x000000ff)) / 255.0f}
{
}

constexpr color::color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) :
    r{static_cast<float>(r) / 255.0f},
    g{static_cast<float>(g) / 255.0f},
    b{static_cast<float>(b) / 255.0f},
    a{static_cast<float>(a) / 255.0f}
{
}

constexpr color::color(const float r, const float g, const float b, const float a) :
    r{r}, g{g}, b{b}, a{a}
{
}

inline constexpr color color::black(0.0f, 0.0f, 0.0f, 1.0f);
inline constexpr color color::white(1.0f, 1.0f, 1.0f, 1.0f);

}
