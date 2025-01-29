#pragma once

#include <enborodo/rendering/texture.hpp>

namespace en
{

class EN_API gl_texture final : public texture
{
public:
    gl_texture();

    ~gl_texture() override;

    void load_from_image(const image& image) override;

    [[nodiscard]]
    unsigned int get_handle() const;

private:
    unsigned int m_handle = 0;
};

}
