#pragma once
#include <enborodo/platform/rendering/gl/gl_index_buffer.hpp>
#include <enborodo/platform/rendering/gl/gl_vertex_buffer.hpp>
#include <enborodo/rendering/model.hpp>

namespace en
{

class EN_API gl_model final : public model
{
public:
    ~gl_model() override = default;

    void load_from_mesh(const mesh& mesh) override;

    [[nodiscard]]
    const gl_vertex_buffer& get_vertex_buffer() const noexcept;

    [[nodiscard]]
    const gl_index_buffer& get_index_buffer() const noexcept;

    [[nodiscard]]
    unsigned int get_vertex_array_handle() const;

private:
    unsigned int m_vao = 0;
    gl_vertex_buffer m_vertex_buffer;
    gl_index_buffer m_index_buffer;
};

}
