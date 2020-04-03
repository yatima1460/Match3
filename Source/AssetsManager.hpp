
#pragma once

#include <map>
#include <assert.h>
#include "TextureData.hpp"

// TODO: default texture in case of error?

class AssetsManager
{


private:

    static std::map<std::string, TextureData*> Textures;

    static TextureData* DEFAULT_TEXTURE;

public:


    static void Init(const std::string& assetsDirectory);


    // template<class T>
    // [[nodiscard]] inline static T& Get(const std::string& name)
    // {
    //     return *reinterpret_cast<T*>(AssetsManager::T[name]);
    // }


    static TextureData& GetTextureData(const std::string& name)
    {
      

        auto iter = Textures.find(name);
        if (iter != Textures.end() )
        {
              auto e = iter->second;
              assert(e != nullptr);
              return *e;
        }
        else
        {
            assert(DEFAULT_TEXTURE != nullptr);
            return *DEFAULT_TEXTURE;
        }
        

    }

    static void Clean();

};