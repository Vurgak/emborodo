#ifndef _WIN32

#include <enborodo/system/sleep.hpp>

#include <chrono>
#include <thread>

namespace en
{

void sleep(const long milliseconds)
{
    std::this_thread::sleep_for(std::chrono::duration<long, std::milli>(milliseconds));
}

}

#endif
