

#include "Game.hpp"

// we don't want to use SDL2main
#undef main
int main(int argc, char const *argv[])
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game starting...");
    [[unused]] const auto game = Game::Started();
    return EXIT_SUCCESS;
}
