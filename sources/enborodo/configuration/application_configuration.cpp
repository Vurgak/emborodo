#include "application_configuration.hpp"

namespace en
{

application_configuration application_configuration::deserialize(const std::string_view file_path)
{
    application_configuration configuration{};
    const auto configuration_table = toml::parse_file(file_path);
    deserialize_struct(configuration.window, *configuration_table["window"].as_table());
    deserialize_struct(configuration.rendering, *configuration_table["rendering"].as_table());
    deserialize_struct(configuration.logging, *configuration_table["logging"].as_table());
    return configuration;
}

}
