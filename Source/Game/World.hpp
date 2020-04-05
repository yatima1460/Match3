#pragma once

#include "Gem.hpp"
#include <vector>
#include <memory.h>
#include <cassert>
#include <SDL.h>

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

    bool IsFilledWithGems(const WorldData world);

    bool HasHoles(const WorldData world);

    bool AllGemsFell(const WorldData world);

    WorldData Swap(WorldData world, SDL_Point position1, SDL_Point position2);

    inline bool IsCoordinateInside(const World::WorldData& world, const SDL_Point& coord)
    {
        return coord.x >= 0 && coord.y >= 0 && coord.x < world.side && coord.y < world.side;
    }

    WorldData SpawnNewGems(WorldData world);
    // constexpr int GetIndex(const int x, const int y,const int side);

    WorldData Generate(const int side, const std::vector<Gem::GemData> gemData);
    
    WorldData RemoveGemsMatches(WorldData world);

    WorldData ApplyGravity(WorldData world);

    // Returns true if the world position can't be affected by gravity
    bool IsPositionStable(WorldData world, SDL_Point position);
}