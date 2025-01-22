#pragma once

#include <memory>

#include <enborodo/windowing/window.hpp>
#include <enborodo/configuration.hpp>
#include <enborodo/gui/gui_controller.hpp>

namespace en
{

class renderer;

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

    float get_frame_time() const;

    std::unique_ptr<window> m_window{};
    renderer* m_renderer;

private:
    float m_frame_time = 0.0f;
};

}
