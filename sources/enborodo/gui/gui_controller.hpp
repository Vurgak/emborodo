#pragma once

#include <functional>
#include <string>

#include <enborodo/configuration.hpp>

namespace en
{

class gui_window;

class EN_API gui_controller
{
public:
    virtual ~gui_controller() = default;

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual void draw_window(const std::string& title, std::function<void(gui_window&)> draw_fn) = 0;
};

}
