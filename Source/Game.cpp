#include "Game.hpp"

#include "Settings.hpp"
#include "AssetsManager.hpp"
#include <assert.h>
#include "Timer.hpp"
#include <iostream>

#include <time.h>

namespace Game
{

struct BackgroundData
{
};

void MainLoop(GameData game);

GameData Started()
{
    
    GameData game;

    if (!Settings::load())
    {
        std::cout << "Can't load settings from .ini file" << std::endl;
        abort();
    }

    //The asset manager needs an OpenGL context to create the textures, so we initialize graphics first
    game.graphics = Graphics::Init();

    // Load all the files inside the input directory
    AssetsManager::Init(game.graphics, Settings::get<std::string>("assets_path"));


    game.registry = new entt::DefaultRegistry();

    // world = new World();
    // Entity backgroundEntity = world->CreateEntity();
    // world->AttachComponent(backgroundEntity, AssetsManager::GetTextureData("background"));
    // world->AttachComponent(backgroundEntity, new Background());

    auto background_entity = game.registry->create();
    game.registry->assign<TexturePointerData>(background_entity, AssetsManager::GetTextureData("background"));
    game.registry->assign<BackgroundData>(background_entity);

    std::vector<std::string> gems = {"ruby", "sapphire", "topaz", "diamond"};

    srand(time(NULL));
    for (size_t x = 0; x < 10; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            auto gem = game.registry->create();

            int randNum = rand() % (gems.size());
            const TexturePointerData diamondTexture = AssetsManager::GetTextureData(gems[randNum]);

            game.registry->assign<TexturePointerData>(gem, diamondTexture);

            const unsigned int textureSize = 64;
            SDL_Point p;
            p.x = x * textureSize;
            p.y = y * textureSize;
            game.registry->assign<SDL_Point>(gem, p);
        }
    }

    
    MainLoop(game);
    game = Cleaned(game);

    return game;
}

GameData Cleaned(GameData game)
{
    AssetsManager::Clean();
    // delete assetManager;
    // assetManager = nullptr;
    std::cout << "Asset Manager cleaned" << std::endl;

    game.graphics = Graphics::Cleaned(game.graphics);
    std::cout << "Graphics cleaned" << std::endl;

    
    std::cout << "Engine cleaned" << std::endl;

    return game;
}

void MainLoop(GameData game)
{
    // Main loop

    std::cout << "Starting mainloop now..." << std::endl;

    Timer::TimerData timer;
    while (!game.quit)
    {
        timer = Timer::Ticked(timer);
        while (SDL_PollEvent(&game.e) != 0)
        {
            switch (game.e.type)
            {
            case SDL_QUIT:
            {
                // Pressing the SDLWindow [X] closes
                game.quit = true;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch (game.e.key.keysym.sym)
                {
                // ESC closes
                case SDLK_ESCAPE:
                    game.quit = true;
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

    

        Graphics::ClearBuffers(game.graphics);

        game.registry->view<BackgroundData, TexturePointerData>().each([game]([[unused]] const auto entity, const auto &BackgroundData, const auto &TextureData) {
            DrawTexture(game.graphics, TextureData);
        });

        game.registry->view<SDL_Point, TexturePointerData>().each([game]([[unused]] const auto entity, const auto &PositionData, const auto &TextureData) {
            DrawTexture(game.graphics, TextureData, PositionData);
        });

        // timer = Timer::FPS(timer);
        // std::cout << timer.FPS << std::endl;
        // auto entities = world->GetAllComponentsOfTypes<Texture, Background>();
        // for (auto entity : entities)
        // {
        //     auto texture = std::get<0>(entity);
        //     auto background = std::get<1>(entity);

        // }

        // const auto& background = AssetsManager::Get<Texture>("background");

        // currentLevel->Update();

        // currentLevel->Draw();

        Graphics::SwapBuffers(game.graphics);
    }
}
} // namespace Game



//struct Game::GameData game;
