#pragma once

#include <enborodo/gui/gui_window.hpp>

namespace en
{

class monotonic_allocator;

class EN_API imgui_gui_window final : public gui_window
{
public:
    explicit imgui_gui_window(monotonic_allocator& allocator);

    void text(const std::string& string) override;

private:
    monotonic_allocator& m_allocator;
};

}
