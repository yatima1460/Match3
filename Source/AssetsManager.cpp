#include "AssetsManager.hpp"

#include <fstream>
#include <assert.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::string AssetManager::assets_folder;

// std::map<std::string, std::unique_ptr<Font>> AssetManager::font_files;
std::map<std::string, TexturePointer::TexturePointerData> AssetManager::texture_files;
std::map<std::string, std::string> AssetManager::text_files;

#if defined(WIN32) || defined(WIN64)
// Copied from linux libc sys/stat.h:
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)
#endif

int is_regular_file(const char *path)
{
    assert(path != NULL);
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDir(const char *file_path)
{
    struct stat s;
    stat(file_path, &s);
    return S_ISDIR(s.st_mode);
}

void AssetManager::Unload()
{

    //font_files.clear();
    texture_files.clear();
    text_files.clear();

    //logger->info("Asset manager cleaned");
}

bool AssetManager::LoadFile(const fs::directory_entry de, Graphics::GraphicsData graphics)
{
    //FIXME: error if key already exists

    const fs::path &path = de.path();
    const std::string ext = path.extension().string();
    assert(!ext.empty());

    //TODO: ugly
    const std::string filename = path.filename().string().substr(0, path.filename().string().length() - ext.length());
    const std::string path_str = path.string();
    //const char *path_c_str = path_str.c_str();

    if (ext == ".ttf")
    {
        // font_files[filename] = std::make_unique<Font>(path_str, 18);
        // assert(font_files[filename] != nullptr);
        return true;
    }
    else if (ext == ".png")
    {
        //load as texture

        texture_files[filename] = LoadTextureFromPNG(graphics, path_str);

        return true;
    }
    else if (ext == ".glsl" || ext == ".lua" || ext == ".ini" || ext == ".txt" || ext == ".json" || ext == ".py")
    {
        //load as text file
        std::ifstream ifs(path_str);
        std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        text_files[filename] = content;
        assert(!text_files[filename].empty());
        return true;
    }

    //logger->critical("Can't load file '{0}' no loading method was implemented", path.string());
    //game->Crash("Can't load file '"+path_str+"' no loading method was implemented");

    return false;
}

bool AssetManager::Init(const std::string assets_folder, Graphics::GraphicsData graphics)
{

    //logger->info("Initializing asset manager");
    assert(!assets_folder.empty());
    AssetManager::assets_folder = assets_folder;

    if (!isDir(assets_folder.c_str()))
    {
        // logger->critical("Can't find assets folder '{0}'", assets_folder);
        // game->Crash("Can't find assets folder '"+Config::GAME_ASSETS_FOLDER+"'");
        return false;
    }

    for (const auto &p : fs::recursive_directory_iterator(assets_folder))
    {
        if (!fs::is_directory(p))
        {
            const bool result = AssetManager::LoadFile(p, graphics);
            if (result)
            {
                // logger->debug("File '{0}' loaded", p.path().string());
            }
            else
            {
                // logger->info("Can't load file: {0}", p.path().string());
                // game->Crash("Can't load file:"+p.path().string());
                return false;
            }
        }
    }

    // logger->info("Asset manager loaded.");
    return true;
}

const std::string &AssetManager::GetString(const std::string name)
{
    assert(!text_files.empty());
    return text_files[name];
}

 SDL_Surface *AssetManager::LoadSDLSurfaceFromPNG(const std::string path)
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