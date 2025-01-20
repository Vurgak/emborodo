#pragma once

#include <enborodo/application.hpp>

namespace em
{

class game : public en::application
{
public:
    game(std::string_view name, int width, int height);

private:
    void update(float delta_time) override;
    void render() const override;
};

}
