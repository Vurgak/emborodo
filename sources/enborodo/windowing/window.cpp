#include "window.hpp"

#include <format>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>

namespace en
{

std::unique_ptr<window> window::create(const window_backend backend)
{
    switch (backend)
    {
        case window_backend::glfw:
            return std::make_unique<glfw_window>();
        default:
            throw std::out_of_range{std::format("window backend \"{}\" isn't implemented", to_string(backend))};
    }
}

}
