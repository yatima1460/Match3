#include "Game.hpp"

#include "Settings.hpp"
#include "AssetsManager.hpp"
#include <assert.h>
#include "Timer.hpp"
#include <iostream>
#include "ECS/Entity.hpp"

#include "ECS/Components/Background.hpp"




Game* game;

struct BackgroundData
{

};

void Game::Start()
{
    if (!Settings::load())
    {
        std::cout << "Can't load settings from .ini file" << std::endl;
        abort();
    }


    //The asset manager needs an OpenGL context to create the textures, so we initialize graphics first
    graphics = new Graphics();

    // Load all the files inside the input directory
    AssetsManager::Init(Settings::get<std::string>("assets_path"));

    // world = new World();
    // Entity backgroundEntity = world->CreateEntity();
    // world->AttachComponent(backgroundEntity, AssetsManager::GetTextureData("background"));
    // world->AttachComponent(backgroundEntity, new Background());

    auto background_entity = registry.create();
    registry.assign<TextureData>(background_entity,AssetsManager::GetTextureData("background"));
    registry.assign<BackgroundData>(background_entity);


    for (size_t x = 0; x < 10; x++)
    {
         for (size_t y = 0; y < 10; y++)
        {
             auto gem = registry.create();
            const TextureData diamondTexture = AssetsManager::GetTextureData("diamond");

             registry.assign<TextureData>(gem,diamondTexture);


            const unsigned int textureSize = 64;
            SDL_Point p;
            p.x = x*textureSize;
            p.y = y*textureSize;
            registry.assign<SDL_Point>(gem,p);
        }
    }
   

    
    this->MainLoop();

    this->Clean();
}

void Game::Clean()
{
    AssetsManager::Clean();
    // delete assetManager;
    // assetManager = nullptr;
    std::cout << "Asset Manager cleaned" << std::endl;

    delete graphics;
    graphics = nullptr;
    std::cout << "Graphics cleaned" << std::endl;

    delete game;
    game = nullptr;
    std::cout << "Engine cleaned" << std::endl;
    
}



void Game::MainLoop()
{
    // Main loop

    std::cout << "Starting mainloop now..." << std::endl;

    Timer::TimerData timer;
    while (!Game::quit)
    {
        timer = Timer::Ticked(timer);
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

        graphics->ClearBuffers();


    registry.view<BackgroundData, TextureData>().each([this](const auto entity, const auto& BackgroundData, const auto& TextureData) {
        graphics->DrawTexture(TextureData);
    });


    registry.view<SDL_Point, TextureData>().each([this](const auto entity, const auto& PositionData, const auto& TextureData) {

        
        graphics->DrawTexture(TextureData, PositionData);
    });

    timer = Timer::FPS(timer);
    std::cout << timer.FPS << std::endl;
        // auto entities = world->GetAllComponentsOfTypes<Texture, Background>();
        // for (auto entity : entities)
        // {
        //     auto texture = std::get<0>(entity);
        //     auto background = std::get<1>(entity);


        // }


       // const auto& background = AssetsManager::Get<Texture>("background");
       
       

        // currentLevel->Update();

        // currentLevel->Draw();

        graphics->SwapBuffers();
    }
}