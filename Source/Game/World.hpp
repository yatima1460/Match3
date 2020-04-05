#pragma once

#include "Gem.hpp"
#include <vector>
#include <memory.h>
#include <cassert>
#include <SDL.h>
#include "Vector2i.hpp"

namespace World
{
struct WorldData
{
    int side = 0;
    std::vector<std::vector<Gem::GemData>> data;
    std::vector<Gem::GemData> gemData;
};

bool IsFilledWithGems(const WorldData world);

bool HasHoles(const WorldData world);

WorldData Swap(WorldData world, Vector2i position1, Vector2i position2);

inline bool IsCoordinateInside(const World::WorldData &world, const Vector2i &coord)
{
    return coord.x >= 0 && coord.y >= 0 && coord.x < world.side && coord.y < world.side;
}

WorldData SpawnNewGems(WorldData world);

WorldData Generate(const int side, const std::vector<Gem::GemData> gemData);

WorldData RemoveGemsMatches(WorldData world);

WorldData ApplyGravity(WorldData world, const int pixelsPerFrame);

// Returns true if the position can't be affected by gravity
bool IsPositionStable(WorldData world, Vector2i position);

} // namespace World