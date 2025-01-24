#ifdef _WIN32

#include <enborodo/system/sleep.hpp>

#include <windows.h>

namespace en
{

// Gets the minimum supported timer resolution and sets it for the Sleep invokation.
// This ensures correct sleep times on Windows.
void sleep(const long milliseconds)
{
    static const auto periodMin = []
    {
        TIMECAPS tc;
        timeGetDevCaps(&tc, sizeof(TIMECAPS));
        return tc.wPeriodMin;
    }();

    timeBeginPeriod(periodMin);
    Sleep(milliseconds);
    timeEndPeriod(periodMin);
}

}

#endif
