#pragma once

#include "TexturePointerData.hpp"
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

[[nodiscard]] GraphicsData Cleaned(GraphicsData);

// void CreateWindow();

/**
     * Draws a texture to point 0,0, using the texture size as destination rectangle
     * @param Texture
     */
void DrawTexture(GraphicsData graphics, const TexturePointerData &Texture);

// void DrawTexture(Texture& texture, SDL_Rect* dest);

/**
     * Draws a texture to point Position, using the texture size as destination rectangle
     * @param texture
     * @param point
     */
void DrawTexture(GraphicsData graphics, const TexturePointerData &texture, const SDL_Point &point);

/**
     * Swaps the graphics buffer, sends the image to the monitor
     */
void SendBufferToScreen(GraphicsData);

[[nodiscard]] SDL_Rect MeasureText(GraphicsData graphics, const std::string &String);

void DrawText(GraphicsData graphics, const std::string &Text, SDL_Point Position, SDL_Color Color);

void DrawText(GraphicsData graphics, const std::string &Text, SDL_Point Position, SDL_Color Color, TTF_Font &Font);

[[nodiscard]] SDL_Rect MeasureText(const std::string &String, TTF_Font &Font);

[[nodiscard]] TexturePointerData LoadTextureFromPNG(GraphicsData graphics, const std::string path);

[[nodiscard]] TexturePointerData LoadTextureFromBMP(GraphicsData graphics, const std::string path);



} // namespace Graphics