#pragma once

#include <enborodo/rendering/shader.hpp>

namespace en
{

class EN_API gl_shader final : public shader
{
public:
    void load_from_file(std::string_view vertex_file_path, std::string_view fragment_file_path) override;

    void load_from_binary(std::string_view vertex_file_path, std::string_view fragment_file_path) override;

    void load_from_memory(std::string_view vertex_code, std::string_view fragment_code) override;

    [[nodiscard]]
    unsigned int get_program_handle() const;

    void set_uniform(std::string_view name, const glm::mat4& value) const override;

private:
    unsigned int m_program_handle = 0;
};

}
