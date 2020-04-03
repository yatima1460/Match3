#pragma once

#include <SDL.h>
#include "ECS/World.hpp"
#include <entt/entt.hpp>

class Game
{

    entt::DefaultRegistry registry;
    World* world;
 //static Level* currentLevel;
    bool quit;
    SDL_Event e;
    void Clean();

public:
    void Start();
    void MainLoop();
};


extern Game* game;