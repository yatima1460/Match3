#pragma once

#include <SDL.h>
#include "Rendering/TexturePointer.hpp"
#include "Functional.hpp"

namespace UI
{

struct SelectionData
{
    // Texture to use when the selection hovers on the world
    TexturePointer::TexturePointerData OpenTexture;

    // Texture to use when the first selection is locked
    TexturePointer::TexturePointerData LockedTexture;

    // World grid location of the first selection
    Vector2i FirstSelectionLockedGridPosition;

    // True when the player clicked on a cell
    bool SelectionLocked = false;

    // Prevent drawing the selection at position 0,0 in the start
    bool MouseMovedAtLeastOnce = false;
};

CONST_FUNCTION inline Vector2i ScreenPositionToGridPosition(const Vector2i screenLocation, const int textureSize)
{
    return {(screenLocation.x / textureSize), (screenLocation.y / textureSize)};
}

CONST_FUNCTION inline Vector2i GridPositionToScreenPosition(const Vector2i gridLocation, const int textureSize)
{
    return {gridLocation.x * textureSize, gridLocation.y * textureSize};
}

inline void DrawTextureAtGridPosition(const Graphics::GraphicsData &graphics, const TexturePointer::TexturePointerData &texture, const Vector2i gridPosition, const int gridSize)
{
    const auto positionToDrawSelection = UI::GridPositionToScreenPosition(gridPosition, gridSize);
    Graphics::DrawTexture(graphics, texture, positionToDrawSelection);
}

CONST_FUNCTION inline bool IsNearbyTaxiDistance(const Vector2i &A, const Vector2i &B)
{
    //TODO: maybe less ugly code?
    return ((A.x == B.x && A.y == B.y - 1) || (A.x == B.x && A.y == B.y + 1) || (A.x == B.x + 1 && A.y == B.y) || (A.x == B.x - 1 && A.y == B.y));
}

} // namespace UI
