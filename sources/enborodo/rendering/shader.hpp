#pragma once

#include <memory>
#include <string_view>

#include <glm/mat4x4.hpp>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API shader
{
public:
    virtual ~shader() = default;

    /// Loads the shader from text files.
    virtual void load_from_file(std::string_view vertex_file_path, std::string_view fragment_file_path) = 0;

    /// Loads the shader from binary files.
    virtual void load_from_binary(std::string_view vertex_file_path, std::string_view fragment_file_path) = 0;

    virtual void load_from_memory(std::string_view vertex_code, std::string_view fragment_code) = 0;

    virtual void set_uniform(std::string_view name, float value) const = 0;

    virtual void set_uniform(std::string_view name, glm::vec3 value) const = 0;

    virtual void set_uniform(std::string_view name, const glm::mat4& value) const = 0;
};

using shader_ptr = std::unique_ptr<shader>;

}
