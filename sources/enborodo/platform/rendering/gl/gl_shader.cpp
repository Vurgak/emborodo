#include "gl_shader.hpp"

#include <cstring>

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <enborodo/system/file.hpp>

namespace
{

std::string get_shader_info_log(const unsigned int shader)
{
    int info_log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log(info_log_length, '\0');
    glGetShaderInfoLog(shader, info_log_length, nullptr, info_log.data());
    info_log.resize(std::strlen(info_log.c_str()));
    return info_log;
}

unsigned int compile_shader(const char* source_code, const int type)
{
    const auto shader = glCreateShader(type);
    if (!shader)
    {
        std::cerr << "failed to create shader\n";
        return 0;
    }

    glShaderSource(shader, 1, &source_code, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        const auto info_log = get_shader_info_log(shader);
        std::cerr << "failed to compile shader: " << info_log << '\n';
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

std::string get_program_info_log(const unsigned int program)
{
    int info_log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log(info_log_length, '\0');
    glGetProgramInfoLog(program, info_log_length, nullptr, info_log.data());
    info_log.resize(std::strlen(info_log.c_str()));
    return info_log;
}

unsigned int link_program(const unsigned int vertex_handle, const unsigned int fragment_handle)
{
    const auto program = glCreateProgram();
    if (!program)
    {
        std::cerr << "failed to create shader program\n";
        return 0;
    }

    glAttachShader(program, vertex_handle);
    glAttachShader(program, fragment_handle);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        const auto info_log = get_program_info_log(program);
        std::cerr << "failed to link shader program" << info_log << '\n';
        glDetachShader(program, vertex_handle);
        glDetachShader(program, fragment_handle);
        glDeleteShader(vertex_handle);
        glDeleteShader(fragment_handle);
        glDeleteProgram(program);
        return 0;
    }

    glDetachShader(program, vertex_handle);
    glDetachShader(program, fragment_handle);
    glDeleteShader(vertex_handle);
    glDeleteShader(fragment_handle);

    return program;
}

}

namespace en
{

void gl_shader::load_from_file(const std::string_view vertex_file_path, const std::string_view fragment_file_path)
{
    const auto vertex_code = file::read_all_text(vertex_file_path);
    const auto fragment_code = file::read_all_text(fragment_file_path);
    load_from_memory(vertex_code, fragment_code);
}

void gl_shader::load_from_binary(const std::string_view vertex_file_path, const std::string_view fragment_file_path)
{
    (void)vertex_file_path;
    (void)fragment_file_path;
    throw std::runtime_error("function not implemented");
}

void gl_shader::load_from_memory(const std::string_view vertex_code, const std::string_view fragment_code)
{
    const auto vertex_shader = compile_shader(vertex_code.data(), GL_VERTEX_SHADER);
    const auto fragment_shader = compile_shader(fragment_code.data(), GL_FRAGMENT_SHADER);
    const auto program = link_program(vertex_shader, fragment_shader);
    m_program_handle = program;
}

unsigned int gl_shader::get_program_handle() const
{
    return m_program_handle;
}

void gl_shader::set_uniform(const std::string_view name, const glm::mat4& value) const
{
    const auto location = glGetUniformLocation(m_program_handle, name.data());
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

}
