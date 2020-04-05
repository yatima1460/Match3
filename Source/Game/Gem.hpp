#pragma once

#include <string>
#include <SDL.h>
#include "Vector2i.hpp"

namespace Gem
{
struct GemData
{
    std::string id;

    // Used for smooth animations
    Vector2i drawingOffset;
};

} // namespace Gem