#pragma once

#include <SDL.h>

#include "Graphics.hpp"
#include "Game/World.hpp"
#include "Game/Vector2i.hpp"

namespace Game
{

struct SelectionData
{
    // Texture to use when the selection hovers on the world
    TexturePointer::TexturePointerData OpenTexture;

    // Texture to use when the first selection is locked
    TexturePointer::TexturePointerData LockedTexture;

    // World grid location of the first selection
    Vector2i FirstSelectionLockedGridPosition;

    Vector2i SecondSelectionLockedGridPosition;

    // True when the player clicked on a cell
    bool SelectionLocked = false;

    // Prevent drawing the selection at position 0,0 in the start
    bool MouseMovedAtLeastOnce = false;
};


void MainLoop(Graphics::GraphicsData graphics);
void Clean(Graphics::GraphicsData graphics);
void Start();

void DrawLevel(Graphics::GraphicsData graphics, World::WorldData world, TexturePointer::TexturePointerData background, SelectionData selection, Vector2i mouseLocation, const int textureSize);
void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world, const int textureSize);

} // namespace Game

//extern struct Game::GameData game;
