#include "Game.hpp"

#include "Settings.hpp"
#include "AssetsManager.hpp"
#include <assert.h>
#include "Timer.hpp"
#include <iostream>
#include "UI.hpp"
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
    game.graphicsContext = Graphics::Init();

    // Load all the files inside the input directory
    AssetManager::Init(Settings::get<std::string>("assets_path"),game.graphicsContext);

    std::vector<Gem::GemData> gems = {{"ruby"}, {"sapphire"}, {"topaz"}, {"diamond"}};

    game.gemsGrid = World::Generate(Settings::get<int>("world_size"), gems);

    MainLoop(game);
    game = Cleaned(game);

    return game;
}

GameData Cleaned(GameData game)
{
    AssetManager::Unload();
    // delete assetManager;
    // assetManager = nullptr;
    std::cout << "Asset Manager cleaned" << std::endl;

    game.graphicsContext = Graphics::Cleaned(game.graphicsContext);
    std::cout << "Graphics cleaned" << std::endl;

    std::cout << "Engine cleaned" << std::endl;

    return game;
}

void MainLoop(GameData game)
{
    // Main loop

    std::cout << "Starting mainloop now..." << std::endl;

    Timer::TimerData timer;
    
    const auto backgroundTexture = AssetManager::GetTextureData("background");

    game.mouseSelection.OpenTexture = AssetManager::GetTextureData("selection_open");
    game.mouseSelection.LockedTexture = AssetManager::GetTextureData("selection_locked");


    Vector2i mouseScreenPosition;

    
    const auto textureSize = Settings::get<int>("texture_size");

    bool quit = false;
    while (!quit)
    {
        timer = Timer::Ticked(timer);

        while (SDL_PollEvent(&game.e) != 0)
        {
            switch (game.e.type)
            {
            case SDL_MOUSEBUTTONDOWN:
            {
                // Deselect with right click
                if (game.e.button.button == SDL_BUTTON_RIGHT)
                {
                    game.mouseSelection.SelectionLocked = false;
                }
                if (game.e.button.button == SDL_BUTTON_LEFT)
                {
                    // Allow clicking only when world is filled and static && mouse moved at least once
                    if (World::IsFilledWithGems(game.gemsGrid) && game.mouseSelection.MouseMovedAtLeastOnce)
                    {
                        const auto currentMouseGridPosition = UI::ScreenPositionToGridPosition(mouseScreenPosition, textureSize);
                        if (World::IsCoordinateInside(game.gemsGrid, currentMouseGridPosition))
                        {
                            // If the player never selected a cell we allow it
                            if (!game.mouseSelection.SelectionLocked)
                            {
                                // Save the location where the player clicked
                                game.mouseSelection.FirstSelectionLockedGridPosition = currentMouseGridPosition;

                                // Set the selection as locked
                                game.mouseSelection.SelectionLocked = true;
                            }
                            else
                            {
                                // If the player selected one and clicks again we check if the swap can be done
                                //TODO: swap check here

                                if (UI::IsNearbyTaxiDistance(currentMouseGridPosition, game.mouseSelection.FirstSelectionLockedGridPosition))
                                {
                                    const auto swappedGemsWorld = World::Swap(game.gemsGrid, currentMouseGridPosition, game.mouseSelection.FirstSelectionLockedGridPosition);
                                    const auto matchesCalculated = World::RemoveGemsMatches(swappedGemsWorld);
                                    if (!World::IsFilledWithGems(matchesCalculated))
                                    {
                                        // The swapping produced holes, update the world
                                        game.gemsGrid = matchesCalculated;
                                    }
                                    else
                                    {
                                        // Clicked nearby, but swapping failed
                                    }
                                }

                                // Clicked too far or swapping happened
                                game.mouseSelection.SelectionLocked = false;
                            }
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                // Update mouse position when mouse is moved
                mouseScreenPosition.x = game.e.motion.x;
                mouseScreenPosition.y = game.e.motion.y;

                game.mouseSelection.MouseMovedAtLeastOnce = true;
                break;
            }
            case SDL_QUIT:
            {
                // Pressing the SDLWindow [X] closes
                quit = true;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch (game.e.key.keysym.sym)
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

        game.gemsGrid = World::RemoveGemsMatches(game.gemsGrid);

        game.gemsGrid = World::SpawnNewGems(game.gemsGrid);
        game.gemsGrid = World::ApplyGravity(game.gemsGrid, Settings::get<int>("gravityPixelsPerFrame"), textureSize);

        Game::DrawLevel(game.graphicsContext, game.gemsGrid, backgroundTexture, game.mouseSelection, mouseScreenPosition, textureSize);
    }
}

void DrawLevel(Graphics::GraphicsData graphics, World::WorldData world, TexturePointer::TexturePointerData background, SelectionData selection, Vector2i mouseLocation, const int textureSize)
{
    Graphics::ClearBuffers(graphics);
    Graphics::DrawTexture(graphics, background, {0,0});
    Game::DrawWorld(graphics, world, textureSize);

    const auto currentMouseGridPosition = UI::ScreenPositionToGridPosition(mouseLocation, textureSize);

    // Draw selection square only if the world has done the fallings and is static
    if (World::IsFilledWithGems(world))
    {
        // If selection is locked we draw the first one at the saved click position
        if (selection.SelectionLocked)
            UI::DrawTextureAtGridPosition(graphics, selection.LockedTexture, selection.FirstSelectionLockedGridPosition, textureSize);

        // And then draw a second hovering one, but not outside the world
        // This could both be the first one hovering, or the second one hovering
        if (selection.MouseMovedAtLeastOnce && World::IsCoordinateInside(world, currentMouseGridPosition))
            UI::DrawTextureAtGridPosition(graphics, selection.OpenTexture, currentMouseGridPosition, textureSize);
    }

    Graphics::SendBufferToScreen(graphics);
}

void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world, const int textureSize)
{
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {

            const auto gem = world.data[x][y];
            if (!gem.id.empty())
            {
                const auto texture = AssetManager::GetTextureData(gem.id);

                Vector2i pos = {x, y};
                Graphics::DrawTexture(graphics, texture, pos * textureSize + gem.drawingOffset);
            }
        }
    }
}

} // namespace Game
