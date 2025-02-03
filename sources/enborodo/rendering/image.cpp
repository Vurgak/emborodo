#include "image.hpp"

#include <print>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

namespace en
{

void image::load_from_file(const std::string_view file_path)
{
    constexpr int channels = STBI_rgb;
    int width, height;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(file_path.data(), &width, &height, nullptr, channels);
    if (!data)
    {
        std::println("failed to load image \"{}\": {}", file_path, stbi_failure_reason());
        return;
    }

    const auto size = width * height * channels;
    m_data.resize(size);
    std::copy_n(data, size, m_data.begin());

    stbi_image_free(data);

    m_width = width;
    m_height = height;
    m_channels = channels;
}

std::span<const unsigned char> image::get_data() const
{
    return {m_data.data(), m_data.size()};
}

std::size_t image::get_width() const
{
    return m_width;
}

std::size_t image::get_height() const
{
    return m_height;
}

std::size_t image::get_channels() const
{
    return m_channels;
}

}
