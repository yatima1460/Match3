
#pragma once

#include <string>
#include <SDL.h>
#include "Settings.hpp"
#include <assert.h>
#include "ECS/Components/Component.hpp"

struct TexturePointerData
{

    SDL_Texture *internal;
    std::string Path;

    TexturePointerData()
    {
        internal = nullptr;
        Path = "";
    }

    // TexturePointerData(const TexturePointerData &source)
    // {
    //     assert(source.internal != nullptr);
    //     internal = source.internal;
    //     Path = source.Path;
    // }

    // TexturePointerData &operator=(TexturePointerData &&source)
    // {
    //     assert(source.internal != nullptr);
    //     internal = source.internal;

    //     assert(!source.Path.empty());
    //     Path = std::move(source.Path);

    //     return *this;
    // }

    explicit TexturePointerData(const std::string &Path);

   

    [[nodiscard]] SDL_Rect GetSDLRect() const;

    ~TexturePointerData();
}; //Settings::get<std::string>("assets_path")+"/"+