#include "window_backend.hpp"

namespace en
{

std::string_view to_string(const window_backend backend)
{
    switch (backend)
    {
        case window_backend::glfw: return "glfw";
        default: return "unknown";
    }
}


}
