#pragma once

#include <span>
#include <string_view>
#include <vector>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API image
{
public:
    void load_from_file(std::string_view file_path);

    [[nodiscard]]
    std::span<const unsigned char> get_data() const;

    [[nodiscard]]
    std::size_t get_width() const;

    [[nodiscard]]
    std::size_t get_height() const;

private:
    std::size_t m_width = 0;
    std::size_t m_height = 0;
    std::size_t m_channels = 0;
    std::vector<unsigned char> m_data;
};

}
