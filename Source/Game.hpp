#pragma once

#include <SDL.h>

#include "Graphics.hpp"
#include "Game/World.hpp"
#include "Game/Vector2i.hpp"
#include "UI.hpp"
#include <json.hpp>
using json = nlohmann::json;

namespace Game
{

void MainLoop(const json& settings, const Graphics::GraphicsData& graphics);
void Clean(Graphics::GraphicsData graphics);
void Start();

void PollEvents(SDL_Event e, bool& quitted, Vector2i& mouseScreenPosition, UI::SelectionData& mouseSelection, World::WorldData& world,  int textureSize);
void DrawLevel(const Graphics::GraphicsData& graphics, const World::WorldData& world, const TexturePointer::TexturePointerData& background, const UI::SelectionData& selection, const Vector2i& mouseLocation, const int textureSize);
void DrawWorld(const Graphics::GraphicsData& graphics, const World::WorldData& world, const int textureSize);

} // namespace Game
