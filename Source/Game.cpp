#include "Game.hpp"

#include "AssetsManager.hpp"
#include <assert.h>
#include "Timer.hpp"
#include <iostream>
#include "UI.hpp"
#include <sstream>

namespace Game
{

struct BackgroundData
{
};

void Start()
{

    json settings;

    std::ifstream file("Settings.json");

    if (file)
    {

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        settings = settings.parse(buffer.str());
    }
    else
    {
        std::cout << "ERROR: can't load settings file" << std::endl
                  << std::endl;
        abort();
    }

    //The asset manager needs an OpenGL context to create the textures, so we initialize graphics first
    Graphics::GraphicsData graphics = Graphics::Init(settings);

    // Load all the files inside the input directory
    AssetManager::Init(settings["assets_path"], graphics);

    MainLoop(settings, graphics);

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

void MainLoop(const json &settings, const Graphics::GraphicsData &graphics)
{
    // Main loop

    std::cout << "Starting mainloop now..." << std::endl;

    Timer::TimerData timer;

    const auto backgroundTexture = AssetManager::GetTextureData("background");

    UI::SelectionData mouseSelection;
    SDL_Event e;

    // TODO: load gems data from JSON?
    std::vector<Gem::GemData> gems = {Gem::GemData("ruby"), Gem::GemData("sapphire"), Gem::GemData("topaz"), Gem::GemData("diamond"), Gem::GemData("amethyst")};

    auto world = World::GenerateEmpty(settings["world_size"], gems);

    mouseSelection.OpenTexture = AssetManager::GetTextureData("selection_open");
    mouseSelection.LockedTexture = AssetManager::GetTextureData("selection_locked");

    Vector2i mouseScreenPosition = {0, 0};

    const auto textureSize = settings["texture_size"];
    const auto gravityPixelsPerFrame = settings["gravityPixelsPerFrame"];

#ifdef WIN32
    const auto millisecondsForFrame = 1000.0f / settings["FPS"].get<float>();
#endif

    bool quit = false;
    while (!quit)
    {
#ifdef WIN32
        int start = SDL_GetTicks();
#endif

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
                    if (World::IsStatic(world) && mouseSelection.MouseMovedAtLeastOnce)
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

                                const auto areCellsNearby = UI::IsNearbyTaxiDistance(currentMouseGridPosition, mouseSelection.FirstSelectionLockedGridPosition);
                                const auto areBothGemsStatic = world.data[mouseSelection.FirstSelectionLockedGridPosition.x][mouseSelection.FirstSelectionLockedGridPosition.y].animation == Gem::GemState::STATIC && world.data[currentMouseGridPosition.x][currentMouseGridPosition.y].animation == Gem::GemState::STATIC;

                                if (areCellsNearby && areBothGemsStatic)
                                {
                                    const auto swappedGemsWorld = World::Swap(world, currentMouseGridPosition, mouseSelection.FirstSelectionLockedGridPosition);
                                    const auto matchesCalculated = World::RemoveGemsMatches(swappedGemsWorld);

                                    // if the simulated world is different it means there was a match
                                    // so we apply it
                                    if (swappedGemsWorld.data != matchesCalculated.data)
                                    {
                                        world.data = matchesCalculated.data;
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

        world = World::SpawnNewGems(world);
        world = World::CalculateGravity(world);
        world = World::RemoveGemsMatches(world);
        // if (!World::IsStatic(world))
        //

        world = World::ApplyAnimation(world, gravityPixelsPerFrame, textureSize);

        Game::DrawLevel(graphics, world, backgroundTexture, mouseSelection, mouseScreenPosition, textureSize);

#ifdef WIN32
        // on Windows it seems SDL returns that vsync is enabled even when not true, needs more investigation
        int time = SDL_GetTicks() - start;
        if (time < 0)
            continue; // if time is negative, the time probably overflew, so continue asap

        int sleepTime = millisecondsForFrame - time;
        if (sleepTime > 0)
        {
            SDL_Delay(sleepTime);
        }
#endif
    }
}

void DrawLevel(const Graphics::GraphicsData &graphics, const World::WorldData &world, const TexturePointer::TexturePointerData &background, const UI::SelectionData &selection, const Vector2i &mouseLocation, const int textureSize)
{
    Graphics::ClearBuffers(graphics);
    Graphics::DrawTexture(graphics, background, {0, 0});
    Game::DrawWorld(graphics, world, textureSize);

    const auto currentMouseGridPosition = UI::ScreenPositionToGridPosition(mouseLocation, textureSize);

    // Draw selection square only if the world has done the fallings and is static
    if (World::IsStatic(world))
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

void DrawWorld(const Graphics::GraphicsData &graphics, const World::WorldData &world, const int textureSize)
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
                Vector2i drawingOffsetInt;
                drawingOffsetInt.x = (int)gem.drawingOffset.x;
                drawingOffsetInt.y = (int)gem.drawingOffset.y;
                Graphics::DrawTexture(graphics, texture, pos * textureSize + drawingOffsetInt);
            }
        }
    }
}

} // namespace Game
