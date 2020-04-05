
#pragma once

#include <string>
#include <SDL.h>
#include "Settings.hpp"
#include <assert.h>

struct TexturePointerData
{

    SDL_Texture *internal = nullptr;
    std::string Path = "";

private:
    // TexturePointerData(const TexturePointerData &source)
    // {

    // }

    // TexturePointerData &operator=(TexturePointerData &&source)
    // {

    //     return *this;
    // }

public:
    [[nodiscard]] SDL_Rect GetSDLRect() const;

}; //Settings::get<std::string>("assets_path")+"/"+