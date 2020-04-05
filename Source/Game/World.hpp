#pragma once

#include "Gem.hpp"
#include <vector>
#include <memory.h>
#include <cassert>

namespace World
{
    struct WorldData
    {
        int side = 0;
        std::vector<std::vector<Gem::GemData>> data;
        std::vector<Gem::GemData> gemData;

        // WorldData& operator=(WorldData source)
        // {
        //     this->side = source.side;

        //     this->data = new Gem::GemData *[side];
        //     for (int i = 0; i < side; ++i)
        //         this->data[i] = new Gem::GemData[side];

        //     memcpy(this->data, source.data, source.side*source.side);

        //     return *this;
        // }

        // ~WorldData()
        // {
        //     assert(this->data != nullptr);
        //     delete[] this->data;
        // }
    };

    bool IsFilled(const WorldData world);

    WorldData SpawnNewGems(WorldData world);
    // constexpr int GetIndex(const int x, const int y,const int side);

    WorldData Generate(const int side, const std::vector<Gem::GemData> gemData);
    
    WorldData RemoveMatches(WorldData world);

    WorldData ApplyGravity(WorldData world);
}