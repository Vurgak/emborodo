#include "game.hpp"

namespace em
{
game::game(const std::string_view name, const int width, const int height) :
    en::application{name, width, height}
{
}


void game::update(const float delta_time)
{
    (void)delta_time;
}

void game::render() const
{
}

}
