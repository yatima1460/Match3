#pragma once

#include "Texture.hpp"
#include <SDL_ttf.h>

class Graphics
{

private:

    static SDL_Renderer* SDLRenderer;
    static SDL_Window* SDLWindow;
    static TTF_Font* SmallFont;
    static TTF_Font* NormalFont;
    static TTF_Font* BigFont;
    static SDL_Surface* ScreenSurface;

public:
    static void Init();


    static void ClearBuffers();

    //static void CreateWindow();


    /**
     * Draws a texture to point 0,0, using the texture size as destination rectangle
     * @param Texture
     */
    static void DrawTexture(Texture& Texture);

    //static void DrawTexture(Texture& texture, SDL_Rect* dest);

    /**
     * Draws a texture to point Position, using the texture size as destination rectangle
     * @param texture
     * @param point
     */
    static void DrawTexture(const Texture& texture, const SDL_Point& point);

    /**
     * Swaps the graphics buffer, sends the image to the monitor
     */
    static void SwapBuffers();

    [[nodiscard]] static SDL_Renderer* GetSDLRenderer();

    [[nodiscard]] static SDL_Rect MeasureText(const std::string& String);

    [[nodiscard]] static TTF_Font& GetDefaultFont();

    [[nodiscard]] static TTF_Font& GetBigFont();

    [[nodiscard]] static TTF_Font& GetSmallFont();

    static void DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color);

    static void DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color, TTF_Font& Font);

    [[nodiscard]] static SDL_Rect MeasureText(const std::string& String, TTF_Font& Font);

    static void Clean();

};