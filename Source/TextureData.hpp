
#pragma once

#include <string>
#include <SDL.h>
#include "Settings.hpp"
#include <assert.h>
#include "ECS/Components/Component.hpp"

struct TextureData
{

private:

    SDL_Texture* internal;

    

    

public:

    std::string Path;

    TextureData(const TextureData &source) 
    {
        assert(source.internal != nullptr);
        internal = source.internal; 
        Path = source.Path; 

        
    
    } 

    TextureData& operator=(TextureData&& other)
   {
       assert(internal != nullptr);
       internal = other.internal;
       Path = std::move(other.Path);
    

      return *this;
   }
    
    
    explicit TextureData(const std::string& Path);

    //TextureData() : TextureData("Assets/NoTexture.bmp") {};

    [[nodiscard]] SDL_Texture* GetSDLTexture() const;

    [[nodiscard]] SDL_Rect GetSDLRect() const;

    ~TextureData();
};//Settings::get<std::string>("assets_path")+"/"+