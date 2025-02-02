#pragma once
#include <enborodo/platform/rendering/gl/gl_vertex_buffer.hpp>
#include <enborodo/rendering/model.hpp>

namespace en
{

class gl_model final : public model
{
public:
    ~gl_model() override = default;

    void load_from_mesh(const mesh& mesh) override;

    [[nodiscard]]
    std::size_t get_index_count() const noexcept;

    [[nodiscard]]
    unsigned int get_vertex_array_handle() const;

private:
    unsigned int m_vao = 0;

    gl_vertex_buffer vertex_buffer;

    unsigned int m_ebo = 0;
    std::size_t m_index_count = 0;
};

}
