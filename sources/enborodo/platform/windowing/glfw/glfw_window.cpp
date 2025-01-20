#include "glfw_window.hpp"

#include <GLFW/glfw3.h>

namespace en
{

int glfw_window::s_instance_count = 0;

glfw_window::~glfw_window()
{
    close();
}

void glfw_window::open(std::string_view title, int width, int height)
{
    if (!s_instance_count)
    {
        glfwInit();
        s_instance_count++;
    }

    m_handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
}

void glfw_window::close()
{
    if (!is_open())
        return;

    glfwDestroyWindow(m_handle);

    s_instance_count--;
    if (!s_instance_count)
        glfwTerminate();
}

bool glfw_window::is_open()
{
    return m_handle && !glfwWindowShouldClose(m_handle);
}

void glfw_window::poll_events()
{
    glfwPollEvents();
}

void glfw_window::display()
{
    glfwSwapBuffers(m_handle);
}

}
