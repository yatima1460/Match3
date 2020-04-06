#pragma once

#include <string>
#include <map>

#include <memory>
#include "Graphics.hpp"

#if __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
#endif

#include "TexturePointer.hpp"

// #include <Game/Map.hpp>

struct AssetManager
{

public:
    // static std::map<std::string, std::unique_ptr<Font>> font_files;
    static std::map<std::string, TexturePointer::TexturePointerData> texture_files;
    static std::map<std::string, std::string> text_files;

    static std::string assets_folder;

    static bool LoadFile(const fs::directory_entry de, Graphics::GraphicsData graphics);
    static bool Init(const std::string& assets_folder, Graphics::GraphicsData graphic);

    static const std::string &GetString(const std::string& name);
    inline static const TexturePointer::TexturePointerData &GetTextureData(const std::string& name)
    {
        assert(!texture_files.empty());
        assert(texture_files[name].internal != nullptr);
        return texture_files[name];
    }
    // static const Font& GetFont(const std::string name);
     static SDL_Surface *LoadSDLSurfaceFromPNG(const std::string& path);

    static void Unload();
};