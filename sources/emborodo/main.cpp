#include <emborodo/game.hpp>

int main()
{
    auto configuration = en::application_configuration::deserialize(EM_ASSETS_PATH "configuration.toml");

    em::game game{"Emborodo", configuration};
    game.run();
    return 0;
}
