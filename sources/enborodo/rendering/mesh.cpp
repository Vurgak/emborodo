#include "mesh.hpp"

#include <filesystem>
#include <iostream>
#include <print>

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

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
    if (file_path.ends_with(".obj"))
        return load_from_obj_file(file_path);
    if (file_path.ends_with(".glb") || file_path.ends_with(".gltf"))
        return load_from_gltf_file(file_path);
    throw std::runtime_error{std::format("unknown model file extension \"{}\"", file_path)};
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

mesh mesh::load_from_obj_file(const std::string_view file_path)
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

#define FOREACH_C(Iterator, Array, Count, Body) for (auto i = 0; i < Count; ++i) { \
    Iterator = Array[i]; \
    Body \
    }

mesh mesh::load_from_gltf_file(const std::string_view file_path)
{
    constexpr cgltf_options options{};
    cgltf_data* data = nullptr;

    if (const auto parse_result = cgltf_parse_file(&options, file_path.data(), &data); parse_result != cgltf_result_success)
        throw std::runtime_error{std::format("failed to parse mesh file \"{}\"", file_path)};

    if (const auto load_result = cgltf_load_buffers(&options, data, file_path.data()); load_result != cgltf_result_success)
        throw std::runtime_error{std::format("failed to load mesh file buffers \"{}\"", file_path)};

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (auto mesh_index = 0; mesh_index < data->meshes_count; ++mesh_index)
    {
        const auto& mesh = data->meshes[mesh_index];
        for (auto primitive_index = 0; primitive_index < mesh.primitives_count; ++primitive_index)
        {
            const auto& primitive = mesh.primitives[primitive_index];
            for (auto attribute_index = 0; attribute_index < primitive.attributes_count; ++attribute_index)
            {
                const auto& attribute = primitive.attributes[attribute_index];
                if (attribute.type != cgltf_attribute_type_position)
                    continue;

                const auto accessor = attribute.data;

                const cgltf_buffer_view* buffer_view = accessor->buffer_view;
                const auto buffer = reinterpret_cast<float*>(static_cast<char*>(buffer_view->buffer->data) + buffer_view->offset + accessor->offset);

                for (cgltf_size v = 0; v < accessor->count; ++v)
                {
                    const auto stride = accessor->stride / sizeof(float);
                    vertices.push_back(buffer[v * stride + 0]);
                    vertices.push_back(buffer[v * stride + 1]);
                    vertices.push_back(buffer[v * stride + 2]);

                    // TODO: Read texture coordinates.
                    vertices.push_back(0);
                    vertices.push_back(0);
                }
            }

            const cgltf_accessor* indices_accessor = primitive.indices;
            const cgltf_buffer_view* buffer_view = indices_accessor->buffer_view;
            void* data_ptr = static_cast<char *>(buffer_view->buffer->data) + buffer_view->offset + indices_accessor->offset;
            for (cgltf_size v = 0; v < indices_accessor->count; ++v)
            {
                unsigned int index;
                switch (indices_accessor->component_type)
                {
                    case cgltf_component_type_r_8u:
                        index = static_cast<uint8_t*>(data_ptr)[v];
                        break;
                    case cgltf_component_type_r_16u:
                        index = static_cast<uint16_t*>(data_ptr)[v];
                        break;
                    case cgltf_component_type_r_32u:
                        index = static_cast<uint32_t*>(data_ptr)[v];
                        break;
                    default:
                        continue;
                }
                indices.push_back(index);
            }
        }
    }

    cgltf_free(data);
    return mesh{std::move(vertices), std::move(indices)};
}

}
