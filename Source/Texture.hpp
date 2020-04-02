
#pragma once

#include <string>
#include <SDL.h>

class Texture
{

private:

    SDL_Texture* internal;


public:

    explicit Texture(const std::string& Path);

    [[nodiscard]] SDL_Texture* GetSDLTexture() const;

    [[nodiscard]] SDL_Rect GetSDLRect() const;

    ~Texture();
};