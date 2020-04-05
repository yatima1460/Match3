#pragma once


#include <string>
#include <SDL.h>

namespace Gem
{
struct GemData
{
    std::string texture_name;

    // Used for smooth animations
    SDL_Point drawingOffset;

    bool IsFalling;

};




}