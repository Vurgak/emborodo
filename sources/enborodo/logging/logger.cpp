#include "logger.hpp"

#include <enborodo/configuration/application_configuration.hpp>

namespace en
{

logger::logger(const logging_configuration& configuration) :
    m_configuration{configuration}
{
}

void logger::set_minimum_level(const log_level level)
{
    m_configuration.level = level;
}

void logger::log(const log_level level, const std::string& message) const
{
    if (level < m_configuration.level)
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
