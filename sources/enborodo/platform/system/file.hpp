#pragma once

#include <string>

#include <enborodo/configuration.hpp>

namespace en::file
{

EN_API std::string read_all_text(std::string_view path);

}
