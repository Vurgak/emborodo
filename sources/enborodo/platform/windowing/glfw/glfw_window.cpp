#include "glfw_window.hpp"

#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{

std::string_view get_debug_source(const GLenum source)
{
    switch (source)
    {
        case GL_DEBUG_SOURCE_API: return "api";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "window system";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "shader compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "third party";
        case GL_DEBUG_SOURCE_APPLICATION: return "application";
        case GL_DEBUG_SOURCE_OTHER: return "other";
        default: std::unreachable();
    }
}

std::string_view get_debug_type(const GLenum type)
{
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR: return "error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "deprecated behaviour";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "undefined behaviour";
        case GL_DEBUG_TYPE_PORTABILITY: return "portability";
        case GL_DEBUG_TYPE_PERFORMANCE: return "performance";
        case GL_DEBUG_TYPE_MARKER: return "marker";
        case GL_DEBUG_TYPE_PUSH_GROUP: return "push group";
        case GL_DEBUG_TYPE_POP_GROUP: return "pop group";
        case GL_DEBUG_TYPE_OTHER: return "other";
        default: std::unreachable();
    }
}

std::string_view get_debug_severity(const GLenum type)
{
    switch (type)
    {
        case GL_DEBUG_SEVERITY_HIGH: return "high";
        case GL_DEBUG_SEVERITY_MEDIUM: return "medium";
        case GL_DEBUG_SEVERITY_LOW: return "low";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "notification";
        default: std::unreachable();
    }
}

void handle_opengl_debug(
    const GLenum source,
    const GLenum type,
    [[maybe_unused]] const unsigned int id,
    const GLenum severity,
    [[maybe_unused]] GLsizei length,
    const char* message,
    [[maybe_unused]] const void* user_param)
{
    const auto debug_source = get_debug_source(source);
    const auto debug_type = get_debug_type(type);
    const auto debug_severity = get_debug_severity(severity);

    std::println(stderr, "{} {} - {} severity: {}", debug_source, debug_type, debug_severity, message);
}

}

namespace en
{

int glfw_window::s_instance_count = 0;

glfw_window::glfw_window(
        const window_configuration& window_configuration,
        const rendering_configuration& rendering_configuration) :
    m_configuration{window_configuration},
    m_rendering_configuration{rendering_configuration}
{
}

glfw_window::~glfw_window()
{
    close();
}

void glfw_window::open(const std::string_view title)
{
    if (!s_instance_count)
    {
        glfwInit();
        s_instance_count++;
    }

    bool opened = false;
    switch (m_rendering_configuration.backend)
    {
        case renderer_backend::opengl:
            opened = open_with_opengl(title);
            break;
    }

    if (!opened)
    {
        // TODO: Use logger.
        const char* message;
        glfwGetError(&message);
        std::println("error: failed to open the game window: {}", message);
    }

    m_input = std::make_unique<glfw_input>(*this);
}

void glfw_window::close()
{
    if (!is_open())
        return;

    m_input = nullptr;
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
    m_input->update();
    glfwPollEvents();
}

input& glfw_window::get_input()
{
    return *m_input;
}

void glfw_window::display()
{
    glfwSwapBuffers(m_handle);
}

window_backend glfw_window::get_backend() const
{
    return window_backend::glfw;
}

void* glfw_window::get_handle()
{
    return m_handle;
}

bool glfw_window::open_with_opengl(const std::string_view title)
{
    glfwWindowHint(GLFW_RESIZABLE, m_configuration.resizable);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_rendering_configuration.major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_rendering_configuration.minor_version);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, m_rendering_configuration.debug);

    m_handle = glfwCreateWindow(m_configuration.width, m_configuration.height, title.data(), nullptr, nullptr);
    if (!m_handle)
        return false;

    glfwSetWindowUserPointer(m_handle, this);
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(m_configuration.vsync ? 1 : 0);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    if (m_rendering_configuration.debug)
    {
        int context_flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
        if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(handle_opengl_debug, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
        }
        else
        {
            std::println(stderr, "Error: Failed to initialize OpenGL debug logging");
        }
    }

    return true;
}

}
