#pragma once

#include <SDL.h>

#include <entt/entt.hpp>
#include "Graphics.hpp"

namespace Game
{

struct GameData
{
    Graphics::GraphicsData graphics;
    entt::DefaultRegistry* registry = nullptr;
    
    bool quit = false;
    SDL_Event e;
};

GameData Cleaned(GameData);
GameData Started();



} // namespace Game

//extern struct Game::GameData game;
