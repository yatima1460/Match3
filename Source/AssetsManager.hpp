
#pragma once

#include <map>
#include <assert.h>
#include "TexturePointerData.hpp"

// TODO: default texture in case of error?

class AssetsManager
{


private:

    static std::map<std::string, TexturePointerData> Textures;

    static TexturePointerData DEFAULT_TEXTURE;

public:


    static void Init(const std::string& assetsDirectory);


    // template<class T>
    // [[nodiscard]] inline static T& Get(const std::string& name)
    // {
    //     return *reinterpret_cast<T*>(AssetsManager::T[name]);
    // }


    static TexturePointerData GetTextureData(const std::string& name)
    {
      

        auto iter = Textures.find(name);
        if (iter != Textures.end() )
        {
              auto e = iter->second;
              
              return e;
        }
        else
        {
            assert(DEFAULT_TEXTURE.internal != nullptr);
            return DEFAULT_TEXTURE;
        }
        

    }

    static void Clean();

};