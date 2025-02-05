#pragma once

#include <memory>

#include <enborodo/configuration.hpp>
#include <enborodo/rendering/camera.hpp>
#include <enborodo/rendering/renderer_backend.hpp>
#include <enborodo/rendering/color.hpp>
#include <enborodo/rendering/model.hpp>
#include <enborodo/rendering/shader.hpp>
#include <enborodo/rendering/texture.hpp>

namespace en
{

class camera;
class texture;

class EN_API renderer
{
public:
    static std::unique_ptr<renderer> create(renderer_backend backend = renderer_backend::opengl);

    virtual ~renderer() = default;

    virtual shader_ptr new_shader() = 0;

    virtual camera_ptr new_camera() = 0;

    virtual texture_ptr new_texture() = 0;

    virtual model_ptr new_model() = 0;

    virtual void clear(color color = color::black) = 0;

    virtual void render(const shader& shader, const model& model, const texture& texture) const = 0;

    virtual void set_camera(camera& camera) = 0;
};

using renderer_ptr = std::unique_ptr<renderer>;

}
