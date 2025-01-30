#include "logger.hpp"

namespace en
{

void logger::set_minimum_level(const log_level level)
{
    m_minimum_level = level;
}

void logger::log(const log_level level, const std::string& message) const
{
    if (level < m_minimum_level)
        return;

    const log_event log_event
    {
        .level = level,
        .timestamp = std::chrono::system_clock::now(),
        .message = message,
    };

    for (const auto& sink : m_sinks)
    {
        sink->emit(log_event);
    }
}

}
