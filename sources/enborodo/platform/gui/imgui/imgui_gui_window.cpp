#include "imgui_gui_window.hpp"

#include <imgui.h>

namespace en
{

imgui_gui_window::imgui_gui_window(monotonic_allocator& allocator) :
    m_allocator{allocator}
{
}

void imgui_gui_window::text(const std::string& string)
{
    ImGui::Text(string.data());
}

}
