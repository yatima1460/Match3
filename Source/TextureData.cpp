


#include "TextureData.hpp"
#include <string>
#include <SDL_surface.h>
#include <cassert>
#include "Graphics.hpp"


TextureData::TextureData(const std::string& Path)  : Path(Path)
{
    //Load splash image
    assert(!Path.empty());
    SDL_Surface* background_surface = SDL_LoadBMP(Path.c_str());
    assert(background_surface != nullptr);

    internal = SDL_CreateTextureFromSurface(Graphics::GetSDLRenderer(), background_surface);
    assert(internal != nullptr);

    assert(background_surface != nullptr);
    SDL_FreeSurface(background_surface);
}


SDL_Texture* TextureData::GetSDLTexture() const
{
    return internal;
}

SDL_Rect TextureData::GetSDLRect() const
{
    SDL_Rect size = {0, 0, 0, 0};
    assert(internal != nullptr);
    SDL_QueryTexture(internal, nullptr, nullptr, &size.w, &size.h);
    return size;
}

TextureData::~TextureData()
{
    //assert(internal != nullptr);
    //SDL_DestroyTexture(internal);
}
