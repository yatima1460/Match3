#pragma once

#include <SDL.h>
#include "ECS/World.hpp"

class Game
{

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