#pragma once

#include <memory>

namespace en
{

class mesh;

class model
{
public:
    virtual ~model() = default;

    virtual void load_from_mesh(const mesh& mesh) = 0;

    virtual const mesh* get_mesh() const = 0;
};

using model_ptr = std::unique_ptr<model>;

}
