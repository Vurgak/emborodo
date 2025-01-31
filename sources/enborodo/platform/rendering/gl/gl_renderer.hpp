#pragma once

#include <enborodo/rendering/renderer.hpp>
#include <enborodo/configuration.hpp>

namespace en
{

class texture;

class EN_API gl_renderer final : public renderer
{
public:
    shader_ptr new_shader() override;

    model_ptr new_model() override;

    texture_ptr new_texture() override;

    camera_ptr new_camera() override;

    void clear(color color) override;

    void render(const shader& shader, const model& model, const texture& texture) const override;

    void set_camera(camera& camera) override;

private:
    camera* m_camera = nullptr;
};

}
