#pragma once

#include <SDL.h>
#include "TexturePointer.hpp"

namespace UI
{

inline Vector2i ScreenPositionToGridPosition(const Vector2i screenLocation, const int textureSize)
{
    return {(screenLocation.x / textureSize), (screenLocation.y / textureSize)};
}

inline Vector2i GridPositionToScreenPosition(const Vector2i gridLocation, const int textureSize)
{
    return {gridLocation.x * textureSize, gridLocation.y * textureSize};
}

inline void DrawTextureAtGridPosition(Graphics::GraphicsData graphics, TexturePointer::TexturePointerData texture, Vector2i gridPosition, const int gridSize)
{
    const auto positionToDrawSelection = UI::GridPositionToScreenPosition(gridPosition, gridSize);
    Graphics::DrawTexture(graphics, texture, positionToDrawSelection);
}

inline bool IsNearbyTaxiDistance(const Vector2i &A, const Vector2i &B)
{
    if (A.x == B.x && A.y == B.y - 1)
    {
        return true;
    }
    if (A.x == B.x && A.y == B.y + 1)
    {
        return true;
    }
    if (A.x == B.x + 1 && A.y == B.y)
    {
        return true;
    }
    if (A.x == B.x - 1 && A.y == B.y)
    {
        return true;
    }

    return false;
}

} // namespace UI
