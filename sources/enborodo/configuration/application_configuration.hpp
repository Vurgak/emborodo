#pragma once

#include <boost/pfr.hpp>

#include <magic_enum/magic_enum.hpp>

#include <toml++/toml.hpp>

#include <enborodo/configuration.hpp>
#include <enborodo/logging/log_level.hpp>
#include <enborodo/rendering/renderer_backend.hpp>
#include <enborodo/windowing/window_backend.hpp>

namespace en
{

struct window_configuration
{
    window_backend backend;
    int width;
    int height;
    bool resizable;
    bool vsync;
    int fps_limit;
};

struct rendering_configuration
{
    renderer_backend backend;
    int major_version;
    int minor_version;
    bool debug;
};

struct logging_configuration
{
    log_level level;
};

class EN_API application_configuration
{
public:
    [[nodiscard]]
    static application_configuration deserialize(std::string_view file_path);

    window_configuration window;
    rendering_configuration rendering;
    logging_configuration logging;

private:
    template <typename TStruct>
    static void deserialize_struct(TStruct& target, const toml::table& table);

    template <typename TEnum>
    static TEnum parse_enum(const toml::node* node);
};

template<typename TStruct>
void application_configuration::deserialize_struct(TStruct& target, const toml::table& table)
{
    boost::pfr::for_each_field(target, [&](auto& field, std::size_t index)
    {
        constexpr auto field_names = boost::pfr::names_as_array<TStruct>();
        const char* field_name = field_names[index].data();

        const toml::node* node = table.get(field_name);
        if (!node) return;

        if constexpr (std::is_same_v<decltype(field), int&>)
        {
            if (const auto* val = node->as_integer())
                field = static_cast<int>(val->get());
        }
        else if constexpr (std::is_same_v<decltype(field), std::string&>)
        {
            if (const auto* val = node->as_string())
                field = val->get();
        }
        else if constexpr (std::is_enum_v<std::decay_t<decltype(field)>>)
        {
            field = parse_enum<std::decay_t<decltype(field)>>(node);
        }
    });
}

template<typename TEnum>
TEnum application_configuration::parse_enum(const toml::node* node)
{
    if (const auto* str = node->as_string())
    {
        const auto result = magic_enum::enum_cast<TEnum>(str->get());
        if (result.has_value()) return result.value();
    }
    throw std::exception{};
}

}
