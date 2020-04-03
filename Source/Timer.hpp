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

/**
 *  Updates the timer and returns a new ticked one
 */
TimerData Ticked(TimerData data);

/**
 *  Gets the deltatime of the input timer
 */
float DeltaTime(const TimerData data);

/**
 *  Refreshes the FPS variable inside the timer
 *   (it's a moving average)
 */
TimerData FPS(TimerData data);

} // namespace Timer