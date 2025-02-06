#include "mesh.hpp"

#include <filesystem>
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace en
{

mesh::mesh(std::vector<vertex>&& vertices, std::vector<unsigned int>&& indices) :
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

    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;

    for (const auto& shape : shapes) {
        for (const auto& [vertex_index, normal_index, tex_coord_index] : shape.mesh.indices) {
            auto& [position, normal, tex_coord] = vertices.emplace_back();

            position.x = attrib.vertices[vertex_index * 3 + 0];
            position.y = attrib.vertices[vertex_index * 3 + 1];
            position.z = attrib.vertices[vertex_index * 3 + 2];

            normal.x = attrib.normals[normal_index * 3 + 0];
            normal.y = attrib.normals[normal_index * 3 + 1];
            normal.z = attrib.normals[normal_index * 3 + 2];

            tex_coord.x = attrib.texcoords[tex_coord_index * 2 + 0];
            tex_coord.y = attrib.texcoords[tex_coord_index * 2 + 1];

            indices.push_back(static_cast<unsigned int>(indices.size()));
        }
    }

    return {std::move(vertices), std::move(indices)};
}

mesh mesh::generate_quad()
{
    return mesh{{
        vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{}, glm::vec2{0.0f, 0.0f}},
        vertex{glm::vec3{ 0.5f, -0.5f, 0.0f}, glm::vec3{}, glm::vec2{1.0f, 0.0f}},
        vertex{glm::vec3{ 0.5f,  0.5f, 0.0f}, glm::vec3{}, glm::vec2{1.0f, 1.0f}},
        vertex{glm::vec3{-0.5f,  0.5f, 0.0f}, glm::vec3{}, glm::vec2{0.0f, 1.0f}},
    }, {
        0, 1, 2, 0, 2, 3
    }};
}

std::span<const vertex> mesh::get_vertices() const
{
    return {m_vertices.data(), m_vertices.size()};
}

std::span<const unsigned> mesh::get_indices() const
{
    return {m_indices.data(), m_indices.size()};
}

}
