#include "renderer_backend.hpp"

namespace en
{

std::string_view to_string(const renderer_backend backend)
{
    switch (backend)
    {
        case renderer_backend::opengl: return "opengl";
        default: return "unknown";
    }
}

}
