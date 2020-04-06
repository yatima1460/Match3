

#include "Game.hpp"
#include <time.h>

// we don't want to use SDL2main
#undef main
int main(int argc, char const *argv[])
{
    // Set random seed for gems spawning
    srand((unsigned int)time(NULL));

    const char *headless = "--headless";
    const char *headless_command = "SDL_VIDEODRIVER=dummy";
    if (argc == 2 && strcmp(argv[1], headless) == 0)
        _putenv((char *)headless_command);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game starting...");
    Game::Start();
    return EXIT_SUCCESS;
}
