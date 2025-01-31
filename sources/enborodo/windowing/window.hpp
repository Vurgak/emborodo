#pragma once

#include <memory>
#include <string_view>

#include <enborodo/configuration.hpp>
#include <enborodo/configuration/application_configuration.hpp>
#include <enborodo/windowing/window_backend.hpp>

namespace en
{

class EN_API window
{
public:
    static std::unique_ptr<window> create(
        const window_configuration& window_configuration,
        const rendering_configuration& rendering_configuration);

    virtual ~window() = default;

    /// Opens a new window if not currently open.
    virtual void open(std::string_view title) = 0;

    /// Closes the window if opened.
    virtual void close() = 0;

    /// Checks whether the window is opened.
    [[nodiscard]]
    virtual bool is_open() = 0;

    virtual void poll_events() = 0;

    /// Renders everything to the screen.
    virtual void display() = 0;

    [[nodiscard]]
    virtual window_backend get_backend() const = 0;

    [[nodiscard]]
    virtual void* get_handle() = 0;
};

}
