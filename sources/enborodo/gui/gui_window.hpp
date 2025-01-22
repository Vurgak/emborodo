#pragma once

#include <string>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API gui_window
{
public:
    virtual ~gui_window() = default;

    virtual void text(const std::string& string) = 0;
};

}
