#pragma once

#include <memory>
#include <string_view>

#include <enborodo/configuration.hpp>

namespace en
{

class image;

class EN_API texture
{
public:
    virtual ~texture() = default;

    virtual void load_from_image(const image& image) = 0;

    void load_from_file(std::string_view file_path);
};

using texture_ptr = std::unique_ptr<texture>;

}
