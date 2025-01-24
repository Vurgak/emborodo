#include "frame_control.hpp"

#include <format>
#include <iostream>
#include <numeric>
#include <thread>

#include <enborodo/system/sleep.hpp>

namespace en
{

void frame_control::end_frame()
{
    m_previous_frame = m_current_frame;
    m_current_frame = clock::now();

    if (const auto frame_time = get_frame_time(); m_target_frame_time > 0 && frame_time < m_target_frame_time)
    {
        const auto sleep_for = m_target_frame_time - frame_time;
        std::cout << "sleeping for " << sleep_for << " milliseconds" << std::endl;
        sleep(sleep_for);
    }
}

void frame_control::set_target_fps(const int fps)
{
    m_target_frame_time = fps != 0 ? 1000 / fps : 0;
}

long frame_control::get_frame_time() const
{
    const auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_current_frame - m_previous_frame);
    return static_cast<long>(frame_duration.count());
}

float frame_control::get_delta_time() const
{
    const std::chrono::duration<float> frame_time = m_current_frame - m_previous_frame;
    return frame_time.count();
}

}
