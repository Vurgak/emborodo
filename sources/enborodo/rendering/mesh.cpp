#include "mesh.hpp"

#include <filesystem>
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace en
{

mesh::mesh(std::vector<float>&& vertices, std::vector<unsigned int>&& indices) :
    m_vertices{std::move(vertices)}, m_indices{std::move(indices)}
{
}

mesh mesh::load_from_file(const std::string_view file_path)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;

    const auto model_directory = std::filesystem::path(file_path).parent_path().string() + "/";
    const auto loaded = LoadObj(&attrib, &shapes, &materials, &err, file_path.data(), model_directory.c_str());
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!loaded)
        throw std::exception{"failed to load mesh file"};

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[index.vertex_index * 3 + 0]);
            vertices.push_back(attrib.vertices[index.vertex_index * 3 + 1]);
            vertices.push_back(attrib.vertices[index.vertex_index * 3 + 2]);

            vertices.push_back(attrib.texcoords[index.texcoord_index * 2 + 0]);
            vertices.push_back(attrib.texcoords[index.texcoord_index * 2 + 1]);

            indices.push_back(indices.size());
        }
    }

    return {std::move(vertices), std::move(indices)};
}

mesh mesh::generate_quad()
{
    return mesh{{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    }, {
        0, 1, 2, 0, 2, 3
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
