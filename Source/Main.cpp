



#include "Game.hpp"

// we don't want to use SDL2main
#undef main
int main(int argc, char const *argv[])
{
    [[unused]] const auto game = Game::Started();
    return EXIT_SUCCESS;
}
