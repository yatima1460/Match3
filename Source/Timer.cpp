#include "Timer.hpp"

#include <SDL.h>
#include <algorithm>

float clamp(float n, float lower, float upper)
{
    return std::max(lower, std::min(n, upper));
}

#define FPS_LINEAR_INTERPOLATION 0.04

namespace Timer
{

TimerData::TimerData()
{
    NOW = SDL_GetPerformanceCounter();
    LAST = SDL_GetPerformanceCounter();
}

float DeltaTime(const TimerData data)
{
    return ((data.NOW - data.LAST) * 1000.0f / SDL_GetPerformanceFrequency());
}

TimerData FPS(TimerData data)
{
    data.FPS = clamp((float)((1000.0 / DeltaTime(data)) * FPS_LINEAR_INTERPOLATION + data.FPS * (1.0f - FPS_LINEAR_INTERPOLATION)), 1, 1000);
    return data;
}

TimerData Ticked(TimerData data)
{
    data.LAST = data.NOW;
    data.NOW = SDL_GetPerformanceCounter();
    return data;
}

} // namespace Timer