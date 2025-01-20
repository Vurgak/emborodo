#include "glfw_window.hpp"

#include <glad/glad.h>
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

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    m_handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(0);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
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
