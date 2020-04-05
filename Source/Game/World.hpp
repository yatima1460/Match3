#pragma once

#include "Gem.hpp"
#include <vector>


namespace World
{
    struct WorldData
    {
        int side;
        Gem::GemData** data;
    };

    // constexpr int GetIndex(const int x, const int y,const int side);

    WorldData Generate(int side, std::vector<Gem::GemData> gemData);
    
    WorldData RemoveMatches(WorldData world);
}