#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include <enborodo/configuration.hpp>
#include <enborodo/configuration/application_configuration.hpp>
#include <enborodo/windowing/window_backend.hpp>

namespace en
{

class input;

class EN_API window
{
public:
    static std::unique_ptr<window> create(
        const window_configuration& window_configuration,
        const rendering_configuration& rendering_configuration);

    static std::unique_ptr<window> open(
        std::string_view title,
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

    [[nodiscard]]
    virtual glm::ivec2 get_window_size() const = 0;

    virtual void set_cursor_enabled(bool enabled) = 0;

    virtual void set_cursor_position(int horizontal_position, int vertical_position) = 0;

    [[nodiscard]]
    virtual input& get_input() = 0;

    virtual void poll_events() = 0;

    /// Renders everything to the screen.
    virtual void display() = 0;

    [[nodiscard]]
    virtual window_backend get_backend() const = 0;

    [[nodiscard]]
    virtual void* get_handle() = 0;
};

using window_ptr = std::unique_ptr<window>;

}
