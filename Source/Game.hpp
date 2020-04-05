#pragma once

#include <SDL.h>


#include "Graphics.hpp"
#include "Game/World.hpp"


namespace Game
{

struct GameData
{
    Graphics::GraphicsData graphics;

    
    World::WorldData world;
    
    bool quit = false;
    SDL_Event e;
};

GameData Cleaned(GameData);
GameData Started();

void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world);

void PollEvents(GameData& game);

} // namespace Game

//extern struct Game::GameData game;
