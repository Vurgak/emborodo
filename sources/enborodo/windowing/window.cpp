#include "window.hpp"

#include <format>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>

namespace en
{

std::unique_ptr<window> window::create(
    const window_configuration& window_configuration,
    const rendering_configuration& rendering_configuration)
{
    switch (window_configuration.backend)
    {
        case window_backend::glfw:
            return std::make_unique<glfw_window>(window_configuration, rendering_configuration);
        default:
            throw std::out_of_range{std::format("window backend \"{}\" isn't implemented", to_string(window_configuration.backend))};
    }
}

}
