#pragma once

#include "TexturePointer.hpp"
#include <SDL_ttf.h>

namespace Graphics
{

struct GraphicsData
{
     SDL_Renderer *SDLRenderer = nullptr;
     SDL_Window *SDLWindow = nullptr;
     TTF_Font *SmallFont = nullptr;
     TTF_Font *NormalFont = nullptr;
     TTF_Font *BigFont = nullptr;
     SDL_Surface *ScreenSurface = nullptr;
     SDL_GLContext GLContext = nullptr;
};

GraphicsData Init();

void ClearBuffers(GraphicsData graphics);

// Draws a texture to point 0,0, using the texture size as destination rectangle
void DrawTexture(GraphicsData graphics, const TexturePointer::TexturePointerData &Texture);

// Draws a texture to point Position, using the texture size as destination rectangle
void DrawTexture(GraphicsData graphics, const TexturePointer::TexturePointerData &texture, const Vector2i &point);

// Swaps the graphics buffer, sends the image to the monitor
void SendBufferToScreen(GraphicsData);

 SDL_Rect MeasureText(GraphicsData graphics, const std::string &String);

void DrawText(GraphicsData graphics, const std::string &Text, Vector2i Position, SDL_Color Color, TTF_Font &Font);

 SDL_Rect MeasureText(const std::string &String, TTF_Font &Font);

 TexturePointer::TexturePointerData LoadTextureFromPNG(GraphicsData graphics, const std::string path);

 TexturePointer::TexturePointerData LoadTextureFromBMP(GraphicsData graphics, const std::string path);

 void Clean(GraphicsData graphics);

} // namespace Graphics