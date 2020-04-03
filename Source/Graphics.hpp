#pragma once

#include "TexturePointerData.hpp"
#include <SDL_ttf.h>

class Graphics
{

private:

     SDL_Renderer* SDLRenderer;
     SDL_Window* SDLWindow;
     TTF_Font* SmallFont;
     TTF_Font* NormalFont;
     TTF_Font* BigFont;
     SDL_Surface* ScreenSurface;

public:
     Graphics();


     void ClearBuffers();

    // void CreateWindow();


    /**
     * Draws a texture to point 0,0, using the texture size as destination rectangle
     * @param Texture
     */
     void DrawTexture(const TexturePointerData& Texture);

    // void DrawTexture(Texture& texture, SDL_Rect* dest);

    /**
     * Draws a texture to point Position, using the texture size as destination rectangle
     * @param texture
     * @param point
     */
     void DrawTexture(const TexturePointerData& texture, const SDL_Point& point);

    /**
     * Swaps the graphics buffer, sends the image to the monitor
     */
     void SwapBuffers();

    [[nodiscard]]  SDL_Renderer* GetSDLRenderer();

    [[nodiscard]]  SDL_Rect MeasureText(const std::string& String);

    [[nodiscard]]  TTF_Font& GetDefaultFont();

    [[nodiscard]]  TTF_Font& GetBigFont();

    [[nodiscard]]  TTF_Font& GetSmallFont();

     void DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color);

     void DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color, TTF_Font& Font);

    [[nodiscard]]  SDL_Rect MeasureText(const std::string& String, TTF_Font& Font);

    [[nodiscard]] TexturePointerData LoadTextureFromPNG(const std::string path);

    [[nodiscard]] TexturePointerData LoadTextureFromBMP(const std::string path);

     ~Graphics();

};