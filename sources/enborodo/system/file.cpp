#include "file.hpp"

#include <fstream>
#include <sstream>

namespace en
{

std::string file::read_all_text(std::string_view path)
{
    std::ifstream stream{path.data()};
    std::ostringstream text;
    text << stream.rdbuf();
    return text.str();
}

}
