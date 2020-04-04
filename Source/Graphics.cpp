
#include <SDL.h>
#include <SDL_ttf.h>
#include <cassert>
#include "Settings.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "Game.hpp"
#include "TexturePointerData.hpp"

#include "AssetsManager.hpp"


namespace Graphics
{


GraphicsData Init()
{
    GraphicsData gd;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! " <<  SDL_GetError() << std::endl;
        abort();
    }

    

    // SDLWindow = SDL_CreateWindow(
    //         Settings::get<std::string>("window_name").c_str(),
    //         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    //         -1, -1,
    //         SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_RENDERER_ACCELERATED);
    gd.SDLWindow = SDL_CreateWindow(
        Settings::get<std::string>("window_name").c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_RENDERER_ACCELERATED);
    if (gd.SDLWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface = AssetsManager::LoadSDLSurfaceFromPNG((Settings::get<std::string>("assets_path")+"/"+ Settings::get<std::string>("icon_name")).c_str());
    if (surface == nullptr)
        std::cerr << "Application icon is NULL" << std::endl;
    else
        SDL_SetWindowIcon(gd.SDLWindow, surface);
    //TODO: free surface icon

    gd.SDLRenderer = SDL_CreateRenderer(gd.SDLWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    const auto fontPath =
            Settings::get<std::string>("assets_path") + "/" + Settings::get<std::string>("asset_font_name");
    gd.SmallFont = TTF_OpenFont(fontPath.c_str(), 24);
    gd.NormalFont = TTF_OpenFont(fontPath.c_str(), 32);
    gd.BigFont = TTF_OpenFont(fontPath.c_str(), 48);
    if (gd.SmallFont == nullptr)
    {
        fprintf(stderr, "error: SmallFont not found\n");
        exit(EXIT_FAILURE);
    }
    if (gd.NormalFont == nullptr)
    {
        fprintf(stderr, "error: NormalFont not found\n");
        exit(EXIT_FAILURE);
    }
    if (gd.BigFont == nullptr)
    {
        fprintf(stderr, "error: BigFont not found\n");
        exit(EXIT_FAILURE);
    }


    // Get SDLWindow surface
    gd.ScreenSurface = SDL_GetWindowSurface(gd.SDLWindow);

    gd.GLContext = SDL_GL_CreateContext(gd.SDLWindow);

    // Enable VSync
    if (SDL_GL_SetSwapInterval(-1) != 0)
    {
        std::cerr << "Can't enable Adaptive VSync:" << SDL_GetError() << std::endl;
        std::cerr << "Falling back to  Non-Adaptive VSync:" << SDL_GetError() << std::endl;
        if (SDL_GL_SetSwapInterval(1) != 0)
        {
            std::cerr << "Can't enable Non Adaptive VSync:" << SDL_GetError() << std::endl;
        }
        else
        {
            std::cout << "Non-Adaptive VSync enabled" << std::endl;
        }
    }
    else
    {
        std::cout << "Adaptive VSync enabled" << std::endl;
    }

    return gd;
}


GraphicsData Cleaned(GraphicsData graphics)
{
    assert(graphics.SmallFont != nullptr);
    TTF_CloseFont(graphics.SmallFont);
    assert(graphics.NormalFont != nullptr);
    TTF_CloseFont(graphics.NormalFont);
    assert(graphics.BigFont != nullptr);
    TTF_CloseFont(graphics.BigFont);
    graphics.SmallFont = nullptr;
    graphics.NormalFont = nullptr;
    graphics.BigFont = nullptr;
    std::cout << "SDL2TTF cleaned" << std::endl;


    SDL_GL_DeleteContext(graphics.GLContext);
    std::cout << "SDL2 GL Context cleaned" << std::endl;

    //Destroy SDLWindow
    assert(graphics.SDLWindow != nullptr);
    SDL_DestroyWindow(graphics.SDLWindow);
    graphics.SDLWindow = nullptr;
    std::cout << "SDL window cleaned" << std::endl;

    //Quit SDL subsystems
    SDL_Quit();
    std::cout << "SDL cleaned" << std::endl;
}



void DrawTexture(GraphicsData graphics, const TexturePointerData& Texture)
{
    SDL_Rect r = Texture.GetSDLRect();
    assert(r.w != 0);
    assert(r.h != 0);
    assert(graphics.SDLRenderer != nullptr);
    SDL_RenderCopy(graphics.SDLRenderer, Texture.internal, nullptr, &r);
}



void SwapBuffers(GraphicsData graphics)
{
    assert(graphics.SDLRenderer != nullptr);
    SDL_RenderPresent(graphics.SDLRenderer);
}



void ClearBuffers(GraphicsData graphics)
{
    assert(graphics.SDLRenderer != nullptr);
    SDL_SetRenderDrawColor(graphics.SDLRenderer, 100, 149, 237, 255);
    SDL_RenderClear(graphics.SDLRenderer);
}


}
 


// void DrawText(GraphicsData graphics, const std::string& Text, SDL_Point Position, SDL_Color Color, TTF_Font& Font)
// {
//     SDL_Surface* creditsSurface = TTF_RenderText_Blended(&Font, Text.c_str(), Color);

//     // is null if string has length zero
//     if (creditsSurface)
//     {
//         SDL_Texture* creditsTexture = SDL_CreateTextureFromSurface(SDLRenderer, creditsSurface);
//         assert(creditsTexture != nullptr);

//         SDL_Rect Message_rect; //create a rect
//         Message_rect.x = Position.x;  //controls the rect's x coordinate
//         Message_rect.y = Position.y; // controls the rect's y coordinte
//         Message_rect.w = creditsSurface->w; // controls the width of the rect
//         Message_rect.h = creditsSurface->h; // controls the height of the rect

//         assert(creditsSurface != nullptr);
//         SDL_FreeSurface(creditsSurface);

//         assert(SDLRenderer != nullptr);
//         assert(creditsTexture != nullptr);
//         SDL_RenderCopy(SDLRenderer, creditsTexture, nullptr, &Message_rect);

//         assert(creditsTexture != nullptr);
//         SDL_DestroyTexture(creditsTexture);

//     }
// }


// void Graphics::DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color)
// {
//     Graphics::DrawText(Text, Position, Color, Graphics::GetDefaultFont());
// }


TexturePointerData Graphics::LoadTextureFromPNG(GraphicsData graphics, const std::string path)
{
    SDL_Surface* surf = AssetsManager::LoadSDLSurfaceFromPNG(path);
    assert(surf != nullptr);

    TexturePointerData td;
    td.internal =  SDL_CreateTextureFromSurface(graphics.SDLRenderer, surf);
    td.Path = path;

    SDL_FreeSurface(surf);
    return td;
}

TexturePointerData Graphics::LoadTextureFromBMP(GraphicsData graphics, const std::string path)
{

    TexturePointerData td;
    td.Path = path;
    assert(!path.empty());
    SDL_Surface* background_surface = SDL_LoadBMP(path.c_str());
    assert(background_surface != nullptr);

    td.internal = SDL_CreateTextureFromSurface(graphics.SDLRenderer, background_surface);
    assert(td.internal != nullptr);

    assert(background_surface != nullptr);
    SDL_FreeSurface(background_surface);

    return td;
}

SDL_Rect Graphics::MeasureText(const std::string& String, TTF_Font& Font)
{
    SDL_Surface* creditsSurface = TTF_RenderText_Blended(&Font, String.c_str(), {255, 255, 255, 255});

    // is null if string has length zero
    if (creditsSurface)
    {
        SDL_Rect r = creditsSurface->clip_rect;
        assert(creditsSurface != nullptr);
        SDL_FreeSurface(creditsSurface);
        return r;
    }
    SDL_Rect empty = {0, 0, 0, 0};
    return empty;
}

SDL_Rect Graphics::MeasureText(GraphicsData graphics, const std::string& String)
{
    assert(graphics.NormalFont != nullptr);
    return Graphics::MeasureText(String, *graphics.NormalFont);
}


/*
void Graphics::DrawTexture(Texture& texture, SDL_Rect* dest)
{

    auto sdlt = texture.GetSDLTexture();
    assert(sdlt != nullptr);

    assert(SDLRenderer != nullptr);
    assert(dest != nullptr);
    SDL_RenderCopy(SDLRenderer, sdlt, nullptr, dest);
}
*/


void Graphics::DrawTexture(GraphicsData graphics, const TexturePointerData& texture, const SDL_Point& point)
{

    SDL_Rect rec = texture.GetSDLRect();
    assert(rec.w != 0);
    assert(rec.h != 0);

    rec.x = point.x;
    rec.y = point.y;
    

    auto sdlt = texture.internal;
    assert(sdlt != nullptr);

    assert(graphics.SDLRenderer != nullptr);
    SDL_RenderCopy(graphics.SDLRenderer, sdlt, nullptr, &rec);
}

