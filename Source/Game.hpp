#pragma once

#include <SDL.h>


class Game
{

 //static Level* currentLevel;
    bool quit;
    SDL_Event e;
    void Clean();

public:
    void Start();
    void MainLoop();
};


extern Game* game;