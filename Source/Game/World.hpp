#pragma once

#include "Gem.hpp"
#include <vector>


namespace World
{
    struct WorldData
    {
        size_t side;
        std::vector<Gem::GemData> data;
    };


    WorldData Generate(size_t side, std::vector<Gem::GemData> gemData);
    
    
}