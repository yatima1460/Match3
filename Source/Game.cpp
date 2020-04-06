#include "Game.hpp"

#include "Settings.hpp"
#include "AssetsManager.hpp"
#include <assert.h>
#include "Timer.hpp"
#include <iostream>
#include "UI.hpp"



namespace Game
{

struct BackgroundData
{
};



void Start()
{

    

    if (!Settings::load())
    {
        std::cout << "Can't load settings from .ini file" << std::endl;
        abort();
    }

    //The asset manager needs an OpenGL context to create the textures, so we initialize graphics first
    Graphics::GraphicsData graphics = Graphics::Init();

    // Load all the files inside the input directory
    AssetManager::Init(Settings::get<std::string>("assets_path"), graphics);


    MainLoop(graphics);

    Game::Clean(graphics);

}

void Clean(Graphics::GraphicsData graphics)
{
    AssetManager::Unload();
    // delete assetManager;
    // assetManager = nullptr;
    std::cout << "Asset Manager cleaned" << std::endl;

    Graphics::Clean(graphics);
    std::cout << "Graphics cleaned" << std::endl;

    std::cout << "Engine cleaned" << std::endl;

}

void MainLoop(Graphics::GraphicsData graphics)
{
    // Main loop

    std::cout << "Starting mainloop now..." << std::endl;

    Timer::TimerData timer;

    const auto backgroundTexture = AssetManager::GetTextureData("background");

    SelectionData mouseSelection;
    SDL_Event e;
    
    std::vector<Gem::GemData> gems = {{"ruby"}, {"sapphire"}, {"topaz"}, {"diamond"}};

    auto world = World::Generate(Settings::get<int>("world_size"), gems);

    mouseSelection.OpenTexture = AssetManager::GetTextureData("selection_open");
    mouseSelection.LockedTexture = AssetManager::GetTextureData("selection_locked");


	Vector2i mouseScreenPosition = { 0, 0};

    
    const auto textureSize = Settings::get<int>("texture_size");

    bool quit = false;
    while (!quit)
    {
        timer = Timer::Ticked(timer);

        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONDOWN:
            {
                // Deselect with right click
                if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseSelection.SelectionLocked = false;
                }
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    // Allow clicking only when world is filled and static && mouse moved at least once
                    if (World::IsFilledWithGems(world) && mouseSelection.MouseMovedAtLeastOnce)
                    {
                        const auto currentMouseGridPosition = UI::ScreenPositionToGridPosition(mouseScreenPosition, textureSize);
                        if (World::IsCoordinateInside(world, currentMouseGridPosition))
                        {
                            // If the player never selected a cell we allow it
                            if (!mouseSelection.SelectionLocked)
                            {
                                // Save the location where the player clicked
                                mouseSelection.FirstSelectionLockedGridPosition = currentMouseGridPosition;

                                // Set the selection as locked
                                mouseSelection.SelectionLocked = true;
                            }
                            else
                            {
                                // If the player selected one and clicks again we check if the swap can be done
                                //TODO: swap check here

                                if (UI::IsNearbyTaxiDistance(currentMouseGridPosition, mouseSelection.FirstSelectionLockedGridPosition))
                                {
                                    const auto swappedGemsWorld = World::Swap(world, currentMouseGridPosition, mouseSelection.FirstSelectionLockedGridPosition);
                                    const auto matchesCalculated = World::RemoveGemsMatches(swappedGemsWorld);
                                    if (!World::IsFilledWithGems(matchesCalculated))
                                    {
                                        // The swapping produced holes, update the world
                                        world = matchesCalculated;
                                    }
                                    else
                                    {
                                        // Clicked nearby, but swapping failed
                                    }
                                }

                                // Clicked too far or swapping happened
                                mouseSelection.SelectionLocked = false;
                            }
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                // Update mouse position when mouse is moved
                mouseScreenPosition.x = e.motion.x;
                mouseScreenPosition.y = e.motion.y;

                mouseSelection.MouseMovedAtLeastOnce = true;
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

        world = World::RemoveGemsMatches(world);

        world = World::SpawnNewGems(world);
        world = World::ApplyGravity(world, Settings::get<int>("gravityPixelsPerFrame"), textureSize);

        Game::DrawLevel(graphics, world, backgroundTexture, mouseSelection, mouseScreenPosition, textureSize);
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
        
        if (selection.SelectionLocked)
        {
            // If selection is locked we draw the first one at the saved click position
            UI::DrawTextureAtGridPosition(graphics, selection.LockedTexture, selection.FirstSelectionLockedGridPosition, textureSize);

            // And the second one, but only in nearby cells
            if (UI::IsNearbyTaxiDistance(selection.FirstSelectionLockedGridPosition, currentMouseGridPosition) && World::IsCoordinateInside(world, currentMouseGridPosition))
                UI::DrawTextureAtGridPosition(graphics, selection.OpenTexture, currentMouseGridPosition, textureSize);
        }
        else
        {
            // If selection is not locked draw a selection on the cell
            if (selection.MouseMovedAtLeastOnce && World::IsCoordinateInside(world, currentMouseGridPosition))
                UI::DrawTextureAtGridPosition(graphics, selection.OpenTexture, currentMouseGridPosition, textureSize);
        }
        
      

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
