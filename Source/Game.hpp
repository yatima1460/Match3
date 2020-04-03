#pragma once

#include <SDL.h>

#include <entt/entt.hpp>
#include "Graphics.hpp"

class Game
{
    
    entt::DefaultRegistry registry;

 //static Level* currentLevel;
    bool quit;
    SDL_Event e;
    void Clean();
    

public:
    Graphics* graphics;
    void Start();
    void MainLoop();
};


extern Game* game;