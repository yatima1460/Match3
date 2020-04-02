



#include "Game.hpp"

// we don't want to use SDL2main
#undef main
int main(int argc, char const *argv[])
{
    game = new Game();
    game->Start();
    return 0;
}
