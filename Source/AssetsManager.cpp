#include "AssetsManager.hpp"

#include <iostream>
#include <dirent.h>
#include <cassert>
#include "Game.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, TexturePointerData> AssetsManager::Textures;


TexturePointerData AssetsManager::DEFAULT_TEXTURE;

std::string pathAppend(const std::string& p1, const std::string& p2)
{

    char sep = '/';
    std::string tmp = p1;

#ifdef _WIN32
    sep = '\\';
#endif

    if (p1[p1.length()] != sep)
    { // Need to add a
        tmp += sep;                // path separator
        return (tmp + p2);
    } else
        return (p1 + p2);
}

bool hasEnding(std::string const& fullString, std::string const& ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else
    {
        return false;
    }
}

[[nodiscard]] SDL_Surface *AssetsManager::LoadSDLSurfaceFromPNG(const std::string path)
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &orig_format, req_format);
    if (data == NULL)
    {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        exit(1);
    }

    int depth, pitch;
    Uint32 pixel_format;
    if (req_format == STBI_rgb)
    {
        depth = 24;
        pitch = 3 * width; // 3 bytes per pixel * pixels per row
        pixel_format = SDL_PIXELFORMAT_RGB24;
    }
    else
    { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4 * width;
        pixel_format = SDL_PIXELFORMAT_RGBA32;
    }
    
  

    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom((void *)data, width, height,
                                                           depth, pitch, pixel_format);
    
    

    if (surf == NULL)
    {
        SDL_Log("Creating surface failed: %s", SDL_GetError());
        abort();
    }

    return surf;
}

void AssetsManager::Init(const std::string& assetsDirectory)
{
    DIR* dirp = opendir(assetsDirectory.c_str());
    struct dirent* dp;

    while ((dp = readdir(dirp)) != nullptr)
    {

        std::string nameStr(dp->d_name);

        const size_t lastindex = nameStr.find_last_of('.');
        const std::string rawname = nameStr.substr(0, lastindex);

        // if (hasEnding(nameStr, "bmp"))
        // {
           
        //     Textures[rawname] = game->graphics->LoadTextureFromBMP(pathAppend(assetsDirectory, nameStr));
        //     std::cout << "Loaded BMP texture: " << nameStr << std::endl;

        // } 
         if (hasEnding(nameStr, "png"))
        {
            
            Textures[rawname] = game->graphics->LoadTextureFromPNG(pathAppend(assetsDirectory, nameStr));
            std::cout << "Loaded PNG texture: " << nameStr << std::endl;
        }
        else if (hasEnding(nameStr, "wav"))
        {
            // TODO
        } else if (hasEnding(nameStr, "ttf"))
        {
            // TODO
        }


    }

    DEFAULT_TEXTURE = game->graphics->LoadTextureFromPNG(pathAppend(assetsDirectory, Settings::get<std::string>("error_texture")));

    if (closedir(dirp) == 0)
    {
        std::cout << "Assets directory closed: " << assetsDirectory << std::endl;
    }
    else
    {
        std::cerr << "Couldn't close assets directory: " << assetsDirectory << std::endl;
    }
}

void AssetsManager::Clean()
{
  
    // std::map<std::string, void*>::iterator it;

    // for (it = Assets.begin(); it != Assets.end(); it++)
    // {
    //     auto t = reinterpret_cast<Texture*>(it->second);


    //     assert(t != nullptr);

    //     delete t;


    // }

    for (std::pair<std::string, TexturePointerData> element  : Textures)
    {

        SDL_DestroyTexture(element.second.GetSDLTexture());
        std::cout << "Cleaned texture:" << element.second.Path << std::endl;

    }
        
    std::cout << "Cleaned assets manager" << std::endl;

    Textures.clear();
}