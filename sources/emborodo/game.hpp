#pragma once

#include <memory>

#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/application.hpp>
#include <enborodo/rendering/mesh.hpp>
#include <enborodo/rendering/model.hpp>

namespace em
{

class game final : public en::application
{
public:
    game(std::string_view name, int width, int height);

protected:
    void update(float delta_time) override;
    void render() const override;
    void render_gui() const override;

private:
    std::unique_ptr<en::gui_controller> m_gui_controller;

    en::shader_ptr m_shader;

    en::mesh m_triangle_mesh;
    en::model_ptr m_triangle;
};

}
