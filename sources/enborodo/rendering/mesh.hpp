#pragma once

#include <span>
#include <vector>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API mesh
{
public:
    mesh() = default;

    mesh(std::vector<float>&& vertices, std::vector<unsigned int>&& indices);

    [[nodiscard]]
    static mesh generate_quad();

    [[nodiscard]]
    std::span<const float> get_vertices() const;

    [[nodiscard]]
    std::span<const unsigned int> get_indices() const;

private:
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
};

}
