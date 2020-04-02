


#include "Texture.hpp"
#include <string>
#include <SDL_surface.h>
#include <cassert>
#include "Graphics.hpp"


Texture::Texture(const std::string& Path)
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


SDL_Texture* Texture::GetSDLTexture() const
{
    return internal;
}

SDL_Rect Texture::GetSDLRect() const
{
    SDL_Rect size = {0, 0, 0, 0};
    assert(internal != nullptr);
    SDL_QueryTexture(internal, nullptr, nullptr, &size.w, &size.h);
    return size;
}

Texture::~Texture()
{
    assert(internal != nullptr);
    SDL_DestroyTexture(internal);
}
