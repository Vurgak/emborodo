#pragma once
#include <enborodo/rendering/model.hpp>

namespace en
{

class gl_model final : public model
{
public:
    ~gl_model() override = default;

    void load_from_mesh(const mesh& mesh) override;

    const mesh* get_mesh() const override;

    unsigned int get_vertex_array_handle() const;

private:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned int m_ebo = 0;

    const mesh* m_mesh = nullptr;
};

}
