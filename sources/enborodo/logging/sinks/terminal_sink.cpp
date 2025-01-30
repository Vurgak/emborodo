#include "terminal_sink.hpp"

#include <print>

#include <magic_enum/magic_enum.hpp>

namespace en
{

void terminal_sink::emit(const log_event& event)
{
    std::println(stderr, "{} [{}] {}", event.timestamp, magic_enum::enum_name(event.level), event.message);
}

}
