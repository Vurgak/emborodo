#pragma once

#include <memory>

#include <enborodo/configuration.hpp>
#include <enborodo/rendering/renderer_backend.hpp>
#include <enborodo/rendering/color.hpp>
#include <enborodo/rendering/model.hpp>
#include <enborodo/rendering/shader.hpp>

namespace en
{

class EN_API renderer
{
public:
    static std::unique_ptr<renderer> create(renderer_backend backend = renderer_backend::opengl);

    virtual ~renderer() = default;

    virtual shader_ptr new_shader() = 0;

    virtual model_ptr new_model() = 0;

    virtual void clear(color color = color::black) = 0;

    virtual void render(const shader& shader, const model& model) const = 0;
};

}
