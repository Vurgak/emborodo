#include "imgui_gui_controller.hpp"

#include <enborodo/platform/gui/imgui/imgui_gui_window.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace en
{

imgui_gui_controller::imgui_gui_controller(window& window) :
    m_allocator{4096}
{
    ImGui::CreateContext();

    auto& imgui_io = ImGui::GetIO();
    imgui_io.IniFilename = nullptr;
    imgui_io.LogFilename = nullptr;

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window.get_handle()), true);
    ImGui_ImplOpenGL3_Init();
}

imgui_gui_controller::~imgui_gui_controller()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imgui_gui_controller::load_font(const std::string_view file_path, const int size)
{
    const auto& imgui_io = ImGui::GetIO();
    imgui_io.Fonts->AddFontFromFileTTF(file_path.data(), static_cast<float>(size));
}

void imgui_gui_controller::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_gui_controller::end()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_allocator.release();
}

void imgui_gui_controller::draw_window(const std::string& title, const std::function<void(gui_window&)> draw_fn)
{
    const auto window = m_allocator.allocate<imgui_gui_window>(m_allocator);
    if (ImGui::Begin(title.c_str()))
        draw_fn(*window);
    ImGui::End();
}

}
