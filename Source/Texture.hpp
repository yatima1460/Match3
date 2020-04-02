
#pragma once

#include <string>
#include <SDL.h>

#include "ECS/Component.hpp"

class Texture : public Component
{

private:

    SDL_Texture* internal;


public:

    explicit Texture(const std::string& Path);

    [[nodiscard]] SDL_Texture* GetSDLTexture() const;

    [[nodiscard]] SDL_Rect GetSDLRect() const;

    ~Texture();
};