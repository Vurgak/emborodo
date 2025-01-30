#pragma once

#include <chrono>
#include <string>

#include <enborodo/configuration.hpp>
#include <enborodo/logging/log_level.hpp>

namespace en
{

struct EN_API log_event
{
    using time_point = std::chrono::system_clock::time_point;

    log_level level;
    time_point timestamp;
    std::string message;
};

class EN_API log_sink
{
public:
    virtual ~log_sink() = default;

    virtual void emit(const log_event& event) = 0;
};

}
