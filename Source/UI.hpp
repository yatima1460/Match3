#pragma once

#include <SDL.h>


namespace UI
{


    inline SDL_Point ScreenPositionToGridPosition(const SDL_Point screenLocation, const int textureSize)
    {
        return {(screenLocation.x / textureSize), (screenLocation.y / textureSize)};
    }



    inline SDL_Point GridPositionToScreenPosition(const SDL_Point gridLocation, const int textureSize)
    {
        return {gridLocation.x * textureSize, gridLocation.y * textureSize};
    }


inline void DrawTextureAtGridPosition(Graphics::GraphicsData graphics, TexturePointerData texture, SDL_Point gridPosition, const int gridSize)
{
    const auto positionToDrawSelection = UI::GridPositionToScreenPosition(gridPosition, gridSize);
    Graphics::DrawTexture(graphics, texture, positionToDrawSelection);
}


}