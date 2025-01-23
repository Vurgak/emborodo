#pragma once

#include <memory>

#include <enborodo/configuration.hpp>
#include <enborodo/rendering/renderer_backend.hpp>
#include <enborodo/rendering/color.hpp>

namespace en
{

class EN_API renderer
{
public:
    static std::unique_ptr<renderer> create(renderer_backend backend = renderer_backend::opengl);

    virtual ~renderer() = default;

    virtual void clear(color color = color::black) = 0;
};

}
