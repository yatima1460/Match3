#pragma once

#include <SDL.h>

#include "Graphics.hpp"
#include "Game/World.hpp"
#include "Game/Vector2i.hpp"
#include "UI.hpp"

namespace Game
{

void MainLoop(Graphics::GraphicsData graphics);
void Clean(Graphics::GraphicsData graphics);
void Start();

void DrawLevel(Graphics::GraphicsData graphics, World::WorldData world, TexturePointer::TexturePointerData background, UI::SelectionData selection, Vector2i mouseLocation, const int textureSize);
void DrawWorld(Graphics::GraphicsData graphics, World::WorldData world, const int textureSize);

} // namespace Game
