#include "renderer.hpp"

#include <enborodo/platform/rendering/gl/gl_renderer.hpp>

namespace en
{

std::unique_ptr<renderer> renderer::s_instance = nullptr;

renderer& renderer::create()
{
    s_instance = std::make_unique<gl_renderer>();
    return *s_instance;
}

renderer& renderer::get_instance()
{
    return *s_instance;
}

}
