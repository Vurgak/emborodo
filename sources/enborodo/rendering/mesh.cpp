#include "mesh.hpp"

namespace en
{

mesh::mesh(std::vector<float>&& vertices, std::vector<unsigned int>&& indices) :
    m_vertices{std::move(vertices)}, m_indices{std::move(indices)}
{
}

mesh mesh::gen_triangle()
{
    return mesh{{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    }, {
        0, 1, 2
    }};
}

std::span<const float> mesh::get_vertices() const
{
    return {m_vertices.data(), m_vertices.size()};
}

std::span<const unsigned> mesh::get_indices() const
{
    return {m_indices.data(), m_indices.size()};
}

}
