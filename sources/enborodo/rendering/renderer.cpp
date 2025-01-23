#include "renderer.hpp"

#include <format>

#include <enborodo/platform/rendering/gl/gl_renderer.hpp>

namespace en
{

std::unique_ptr<renderer> renderer::create(const renderer_backend backend)
{
    switch (backend)
    {
        case renderer_backend::opengl:
            return std::make_unique<gl_renderer>();
        default:
            throw std::out_of_range{std::format("renderer backend \"{}\" isn't implemented", to_string(backend))};
    }
}

}
