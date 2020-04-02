
#include <SDL.h>
#include <SDL_ttf.h>
#include <cassert>
#include "Settings.hpp"
#include "Graphics.hpp"

SDL_Window* Graphics::SDLWindow;
TTF_Font* Graphics::NormalFont;
TTF_Font* Graphics::BigFont;
TTF_Font* Graphics::SmallFont;
SDL_Renderer* Graphics::SDLRenderer;
SDL_Surface* Graphics::ScreenSurface;

void Graphics::Init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    

    // SDLWindow = SDL_CreateWindow(
    //         Settings::get<std::string>("window_name").c_str(),
    //         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    //         -1, -1,
    //         SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDLWindow = SDL_CreateWindow(
        Settings::get<std::string>("window_name").c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (SDLWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface = SDL_LoadBMP((Settings::get<std::string>("assets_path")+"/"+ Settings::get<std::string>("icon_name")).c_str());
    SDL_SetWindowIcon(SDLWindow, surface);

    SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    const auto fontPath =
            Settings::get<std::string>("assets_path") + "/" + Settings::get<std::string>("asset_font_name");
    SmallFont = TTF_OpenFont(fontPath.c_str(), 24);
    NormalFont = TTF_OpenFont(fontPath.c_str(), 32);
    BigFont = TTF_OpenFont(fontPath.c_str(), 48);
    if (SmallFont == nullptr)
    {
        fprintf(stderr, "error: SmallFont not found\n");
        exit(EXIT_FAILURE);
    }
    if (NormalFont == nullptr)
    {
        fprintf(stderr, "error: NormalFont not found\n");
        exit(EXIT_FAILURE);
    }
    if (BigFont == nullptr)
    {
        fprintf(stderr, "error: BigFont not found\n");
        exit(EXIT_FAILURE);
    }


    // Get SDLWindow surface
    ScreenSurface = SDL_GetWindowSurface(SDLWindow);

    // Enable VSync
    SDL_GL_SetSwapInterval(-1);
}

void Graphics::DrawTexture(Texture& Texture)
{
    SDL_Rect r = Texture.GetSDLRect();

    assert(SDLRenderer != nullptr);
    SDL_RenderCopy(SDLRenderer, Texture.GetSDLTexture(), nullptr, &r);
}

void Graphics::SwapBuffers()
{
    assert(SDLRenderer != nullptr);
    SDL_RenderPresent(SDLRenderer);
}

void Graphics::DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color, TTF_Font& Font)
{
    SDL_Surface* creditsSurface = TTF_RenderText_Blended(&Font, Text.c_str(), Color);

    // is null if string has length zero
    if (creditsSurface)
    {
        SDL_Texture* creditsTexture = SDL_CreateTextureFromSurface(SDLRenderer, creditsSurface);
        assert(creditsTexture != nullptr);

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = Position.x;  //controls the rect's x coordinate
        Message_rect.y = Position.y; // controls the rect's y coordinte
        Message_rect.w = creditsSurface->w; // controls the width of the rect
        Message_rect.h = creditsSurface->h; // controls the height of the rect

        assert(creditsSurface != nullptr);
        SDL_FreeSurface(creditsSurface);

        assert(SDLRenderer != nullptr);
        assert(creditsTexture != nullptr);
        SDL_RenderCopy(SDLRenderer, creditsTexture, nullptr, &Message_rect);

        assert(creditsTexture != nullptr);
        SDL_DestroyTexture(creditsTexture);

    }
}


void Graphics::DrawText(const std::string& Text, SDL_Point Position, SDL_Color Color)
{
    Graphics::DrawText(Text, Position, Color, Graphics::GetDefaultFont());
}

void Graphics::ClearBuffers()
{
    assert(Graphics::SDLRenderer != nullptr);
    SDL_SetRenderDrawColor(Graphics::SDLRenderer, 100, 149, 237, 255);
    SDL_RenderClear(Graphics::SDLRenderer);
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

SDL_Rect Graphics::MeasureText(const std::string& String)
{
    return Graphics::MeasureText(String, Graphics::GetDefaultFont());
}

void Graphics::Clean()
{
    assert(SmallFont != nullptr);
    TTF_CloseFont(SmallFont);
    assert(NormalFont != nullptr);
    TTF_CloseFont(NormalFont);
    assert(BigFont != nullptr);
    TTF_CloseFont(BigFont);
    SmallFont = nullptr;
    NormalFont = nullptr;
    BigFont = nullptr;

    //Destroy SDLWindow
    assert(SDLWindow != nullptr);
    SDL_DestroyWindow(SDLWindow);
    SDLWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
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


void Graphics::DrawTexture(const Texture& texture, const SDL_Point& point)
{

    SDL_Rect rec = texture.GetSDLRect();


    rec.x = point.x;
    rec.y = point.y;

    auto sdlt = texture.GetSDLTexture();
    assert(sdlt != nullptr);

    assert(SDLRenderer != nullptr);
    SDL_RenderCopy(SDLRenderer, sdlt, nullptr, &rec);
}

TTF_Font& Graphics::GetDefaultFont()
{
    assert(NormalFont != nullptr);
    return *NormalFont;
}

TTF_Font& Graphics::GetBigFont()
{
    assert(BigFont != nullptr);
    return *BigFont;
}

TTF_Font& Graphics::GetSmallFont()
{
    assert(SmallFont != nullptr);
    return *SmallFont;
}

SDL_Renderer* Graphics::GetSDLRenderer()
{
    assert(SDLRenderer != nullptr);
    return SDLRenderer;
}
