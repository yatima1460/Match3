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

    // game.registry = new entt::DefaultRegistry();

    // world = new World();
    // Entity backgroundEntity = world->CreateEntity();
    // world->AttachComponent(backgroundEntity, AssetsManager::GetTextureData("background"));
    // world->AttachComponent(backgroundEntity, new Background());

    // auto background_entity = game.registry->create();
    // game.registry->assign<TexturePointerData>(background_entity, );
    // game.registry->assign<BackgroundData>(background_entity);

    //std::vector<std::string> gems = {"ruby", "sapphire", "topaz", "diamond"};

    std::vector<Gem::GemData> gems = {{"ruby"}, {"sapphire"}, {"topaz"}, {"diamond"}};

    

    game.world = World::Generate(10, gems);

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
    const auto background = AssetsManager::GetTextureData("background");

    const auto selection = AssetsManager::GetTextureData("selection");


    game.world = World::RemoveMatches(game.world);
    game.selection_pos = {-1,-1};

    while (!game.quit)
    {
        timer = Timer::Ticked(timer);

        Game::PollEvents(game);

    

        while(!World::IsFilled(game.world))
        {
            game.world = World::RemoveMatches(game.world);
            game.world = World::ApplyGravity(game.world);
            game.world = World::SpawnNewGems(game.world);
        }


        Graphics::ClearBuffers(game.graphics);
        Graphics::DrawTexture(game.graphics, background);
        Game::DrawWorld(game.graphics, game.world);


        if (IsGridPointInsideWorld(GetMouseGridLocation(64), game.world))
            Graphics::DrawTexture(game.graphics, selection,GetMousePixelLocation(64));
        
        Graphics::SwapBuffers(game.graphics);
        

    }
}

bool IsGridPointInsideWorld(SDL_Point pixel, World::WorldData world)
{
    return pixel.x >= 0 && pixel.y >= 0 && pixel.x < world.side && pixel.y < world.side;
}

SDL_Point GetMouseGridLocation(const int textureSize)
{
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);


    return {(mouseX/textureSize), (mouseY/textureSize)};
}

SDL_Point GetMousePixelLocation(const int textureSize)
{
    const auto mwl = GetMouseGridLocation(textureSize);
    return {mwl.x*textureSize, mwl.y*textureSize};
}

void PollEvents(GameData& game)
{
    while (SDL_PollEvent(&game.e) != 0)
    {
        switch (game.e.type)
        {
        case SDL_MOUSEMOTION:
        {
            game.selection_pos.x = game.e.motion.x;
            game.selection_pos.y = game.e.motion.y;

            break;
        }
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
}

void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world)
{
for (int y = 0; y < world.side; y++)
        {
    for (int x = 0; x < world.side; x++)
    {
        
            const auto gem = world.data[x][y];
            if (!gem.texture_name.empty())
            {
                const auto texture = AssetsManager::GetTextureData(gem.texture_name);
                Graphics::DrawTexture(graphics, texture, {x * 64, y * 64});
            }
        }
    }
}

} // namespace Game
