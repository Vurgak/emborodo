#pragma once

#include <span>
#include <string_view>
#include <vector>

#include <enborodo/configuration.hpp>
#include <enborodo/rendering/vertex.hpp>

namespace en
{

class EN_API mesh
{
public:
    mesh() = default;

    mesh(std::vector<vertex>&& vertices, std::vector<unsigned int>&& indices);

    [[nodiscard]]
    static mesh load_from_file(std::string_view file_path);

    [[nodiscard]]
    static mesh generate_quad();

    [[nodiscard]]
    std::span<const vertex> get_vertices() const;

    [[nodiscard]]
    std::span<const unsigned int> get_indices() const;

private:
    std::vector<vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};

}
