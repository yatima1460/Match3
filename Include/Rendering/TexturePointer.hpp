
#pragma once

#include <string>
#include <SDL.h>

#include <assert.h>
#include <Math/Vector2i.hpp>

namespace TexturePointer
{
struct TexturePointerData
{
    SDL_Texture *internal = nullptr;
    std::string Path = "";
};

Vector2i GetSize(const TexturePointer::TexturePointerData &texture);
} // namespace TexturePointer
