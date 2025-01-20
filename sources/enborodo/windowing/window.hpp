#pragma once

#include <string_view>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API window
{
public:
    virtual ~window() = default;

    /// Opens a new window if not currently open.
    virtual void open(std::string_view title, int width, int height) = 0;

    /// Closes the window if opened.
    virtual void close() = 0;

    /// Checks whether the window is opened.
    virtual bool is_open() = 0;

    virtual void poll_events() = 0;

    /// Renders everything to the screen.
    virtual void display() = 0;
};

}
