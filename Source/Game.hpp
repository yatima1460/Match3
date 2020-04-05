#pragma once

#include <SDL.h>


#include "Graphics.hpp"
#include "Game/World.hpp"


namespace Game
{

struct SelectionData
{
    // Texture to use when the selection hovers on the world
    TexturePointerData OpenTexture;

    // Texture to use when the first selection is locked
    TexturePointerData LockedTexture;

    // World grid location of the first selection
    SDL_Point FirstSelectionLockedGridPosition;

    
    SDL_Point SecondSelectionLockedGridPosition;

    // True when the player clicked on a cell
    bool SelectionLocked = false;

    // Prevent drawing the selection at position 0,0 in the start
    bool MouseMovedAtLeastOnce = false;
};

struct GameData
{
    Graphics::GraphicsData graphicsContext;


    SelectionData mouseSelection;

    World::WorldData gemsGrid;
    
    bool quit = false;
    SDL_Event e;
};

GameData Cleaned(GameData);
GameData Started();

void DrawLevel(Graphics::GraphicsData graphics, World::WorldData world, TexturePointerData background, SelectionData selection, SDL_Point mouseLocation);
void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world);


} // namespace Game

//extern struct Game::GameData game;
