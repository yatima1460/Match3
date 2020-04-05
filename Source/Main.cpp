

#include "Game.hpp"
#include <time.h>

// we don't want to use SDL2main
#undef main
int main(int argc, char const *argv[])
{
    // Set random seed for gems spawning
    srand(time(NULL));

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game starting...");
    Game::Start();
    return EXIT_SUCCESS;
}
