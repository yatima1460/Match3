
#pragma once

#include <string>
#include <SDL.h>
#include "Settings.hpp"
#include <assert.h>
#include "Game/Vector2i.hpp"

namespace TexturePointer
{
struct TexturePointerData
{
    SDL_Texture *internal = nullptr;
    std::string Path = "";
};

[[nodiscard]] Vector2i GetSize(const TexturePointer::TexturePointerData texture);
} // namespace TexturePointer
