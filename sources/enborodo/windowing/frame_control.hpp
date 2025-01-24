#pragma once

#include <array>
#include <chrono>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API frame_control
{
public:
    void end_frame();

    void set_target_fps(int fps);

    /// Gets the frame time in milliseconds.
    [[nodiscard]]
    long get_frame_time() const;

    /// Gets the frame time as floating-point number of seconds.
    [[nodiscard]]
    float get_delta_time() const;

private:
    using clock = std::chrono::high_resolution_clock;

    std::chrono::time_point<clock> m_previous_frame{};
    std::chrono::time_point<clock> m_current_frame = clock::now();

    long m_target_frame_time{}; ///< Target frame time in milliseconds.
};

}
