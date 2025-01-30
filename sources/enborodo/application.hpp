#pragma once

#include <memory>

#include <enborodo/configuration.hpp>
#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/rendering/renderer.hpp>
#include <enborodo/windowing/frame_control.hpp>
#include <enborodo/windowing/window.hpp>

namespace en
{

class EN_API application
{
public:
    application(std::string_view name, int width, int height);
    virtual ~application() = default;

    void run();

protected:
    virtual void update(float delta_time) = 0;
    virtual void render() const = 0;
    virtual void render_gui() const = 0;

    std::unique_ptr<window> m_window = nullptr;
    std::unique_ptr<renderer> m_renderer = nullptr;
    std::unique_ptr<en::gui_controller> m_gui_controller;

    frame_control m_frame_control{};
};

}
