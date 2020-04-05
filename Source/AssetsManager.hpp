
#pragma once

#include <map>
#include <assert.h>
#include "TexturePointer.hpp"
#include "Graphics.hpp"

class AssetsManager
{

private:
    static std::map<std::string, TexturePointer::TexturePointerData> Textures;
    static TexturePointer::TexturePointerData DEFAULT_TEXTURE;

public:
    static void Init(Graphics::GraphicsData context, const std::string &assetsDirectory);

    static TexturePointer::TexturePointerData GetTextureData(const std::string &name)
    {

        auto iter = Textures.find(name);
        if (iter != Textures.end())
        {
            auto e = iter->second;

            return e;
        }
        else
        {
            assert(DEFAULT_TEXTURE.internal != nullptr);
            return DEFAULT_TEXTURE;
        }
    }

    [[nodiscard]] static SDL_Surface *LoadSDLSurfaceFromPNG(const std::string path);

    static void Clean();
};