#pragma once

#include <SDL.h>


#include "Graphics.hpp"
#include "Game/World.hpp"


namespace Game
{

struct SelectionData
{
    TexturePointerData OpenTexture;
    TexturePointerData LockedTexture;
    SDL_Point FirstSelectionPixelPosition;
    SDL_Point SecondSelectionPixelPosition;
    SDL_Point FirstSelectionLockedGridPosition;
    SDL_Point SecondSelectionLockedGridPosition;
    bool SelectionActive = false;
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

void DrawLevel(Graphics::GraphicsData graphics, World::WorldData world, TexturePointerData background, SelectionData selection);
bool IsGridPointInsideWorld(SDL_Point pixel, World::WorldData world);
SDL_Point GetMouseGridLocation(const int textureSize);
SDL_Point GetMousePixelLocation(const int textureSize);

void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world);


} // namespace Game

//extern struct Game::GameData game;
