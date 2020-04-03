#pragma once

#include <SDL_types.h>

namespace Timer
{
struct TimerData
{
    Uint64 NOW;
    Uint64 LAST;
    float FPS;

    TimerData();
};

TimerData Ticked(TimerData data);

float DeltaTime(const TimerData data);

TimerData FPS(TimerData data);

} // namespace Timer