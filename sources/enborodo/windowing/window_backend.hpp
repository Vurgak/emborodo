#pragma once

#include <string_view>

#include <enborodo/configuration.hpp>

namespace en
{

enum class window_backend
{
    glfw,
};

EN_API std::string_view to_string(window_backend backend);

}
