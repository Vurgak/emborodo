#pragma once

#include <chrono>
#include <format>
#include <memory>
#include <string>
#include <vector>

#include <enborodo/configuration/application_configuration.hpp>
#include <enborodo/logging/log_level.hpp>
#include <enborodo/logging/sinks/log_sink.hpp>

namespace en
{

struct logging_configuration;

class EN_API logger
{
public:
    explicit logger(const logging_configuration& configuration);

    logger(const logger&) = delete;

    logger& operator=(const logger&) = delete;

    void set_minimum_level(log_level level);

    template <typename TSink, typename... TArgs>
    void add_sink(TArgs&&... args);

    void log(log_level level, const std::string& message) const;

    template <typename... TArgs>
    void log(log_level level, std::format_string<TArgs...> message, TArgs&&... args) const;

private:
    logging_configuration m_configuration;
    std::vector<std::unique_ptr<log_sink>> m_sinks;
};

template<typename TSink, typename ... TArgs>
void logger::add_sink(TArgs&&... args)
{
    m_sinks.emplace_back(std::make_unique<TSink>(std::forward<TArgs>(args)...));
}

template<typename ... TArgs>
void logger::log(const log_level level, const std::format_string<TArgs...> message, TArgs&&... args) const
{
    log(level, std::format(message, std::forward<TArgs>(args)...));
}

}
