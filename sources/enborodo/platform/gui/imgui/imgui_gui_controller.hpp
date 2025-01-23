#pragma once

#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/memory/monotonic_allocator.hpp>
#include <enborodo/windowing/window.hpp>

namespace en
{

class EN_API imgui_gui_controller final : public gui_controller
{
public:
    explicit imgui_gui_controller(window& window);

    ~imgui_gui_controller() override;

    void load_font(std::string_view file_path, int size) override;

    void begin() override;

    void end() override;

    void draw_window(const std::string& title, std::function<void(gui_window&)> draw_fn) override;

private:
    /// The allocator used for the GUI elements.
    monotonic_allocator m_allocator;
};

}
