#pragma once

#include <string_view>

#include <enborodo/configuration.hpp>

namespace en {

enum class renderer_backend
{
    opengl,
};

EN_API std::string_view to_string(renderer_backend backend);

}
