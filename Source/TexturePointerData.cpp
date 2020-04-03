


#include "TexturePointerData.hpp"
#include <string>
#include <SDL_surface.h>
#include <cassert>
#include "Graphics.hpp"
#include "Game.hpp"





SDL_Texture* TexturePointerData::GetSDLTexture() const
{
    return internal;
}

SDL_Rect TexturePointerData::GetSDLRect() const
{
    SDL_Rect size = {0, 0, 0, 0};
    assert(internal != nullptr);
    SDL_QueryTexture(internal, nullptr, nullptr, &size.w, &size.h);
    return size;
}

TexturePointerData::~TexturePointerData()
{
    //assert(internal != nullptr);
    //SDL_DestroyTexture(internal);
}
