#include "Game.hpp"
#include "Graphics.hpp"
#include "Settings.hpp"
#include "AssetsManager.hpp"
#include <assert.h>

#include <iostream>

Game* game;


void Game::Start()
{
    if (!Settings::load())
    {
        std::cout << "Can't load settings from .ini file" << std::endl;
        abort();
    }


    //The asset manager needs an OpenGL context to create the textures, so we initialize graphics first
    Graphics::Init();

    // Load all the files inside the input directory
    AssetsManager::Init(Settings::get<std::string>("assets_path"));

    this->MainLoop();

    this->Clean();
}

void Game::Clean()
{
    AssetsManager::Clean();
    Graphics::Clean();
}


void Game::MainLoop()
{
    // Main loop
    while (!Game::quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
                case SDL_QUIT:
                {
                    // Pressing the SDLWindow [X] closes
                    quit = true;
                    break;
                }
                case SDL_KEYDOWN:
                {
                    switch (e.key.keysym.sym)
                    {
                        // ESC closes
                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                        default:
                            break;

                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        Graphics::ClearBuffers();

        const auto background = AssetsManager::Get<Texture>("background");
        assert(background != nullptr);
        Graphics::DrawTexture(*background);

        // currentLevel->Update();

        // currentLevel->Draw();

        Graphics::SwapBuffers();
    }
}