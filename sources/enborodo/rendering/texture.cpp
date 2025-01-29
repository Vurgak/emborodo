#include "texture.hpp"

#include <enborodo/rendering/image.hpp>

namespace en
{

void texture::load_from_file(std::string_view file_path)
{
    image image{};
    image.load_from_file(file_path);
    return load_from_image(image);
}

}
