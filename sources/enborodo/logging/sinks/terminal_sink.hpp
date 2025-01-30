#pragma once

#include <enborodo/logging/sinks/log_sink.hpp>

namespace en
{

class EN_API terminal_sink final : public log_sink
{
public:
    void emit(const log_event& event) override;
};

}
