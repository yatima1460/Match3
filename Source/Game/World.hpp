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
    std::vector<Gem::GemData> gemData;
    std::vector<std::vector<Gem::GemData>> data;
};

WorldData CalculateGravity(WorldData);

// Returns true if there are no holes in the world and all gems are stable
bool IsStatic(const WorldData& world);

// Directly swaps two gems, doesn't care about distances or rules
WorldData Swap(WorldData world, const Vector2i& position1, const Vector2i& position2);

// Returns true if the x,y coordinate is valid
CONST_FUNCTION inline bool IsCoordinateInside(const World::WorldData& world, const Vector2i coord)
{
    return coord.x >= 0 && coord.y >= 0 && coord.x < world.side && coord.y < world.side;
}

// Spawn gems in empty holes of the first row
WorldData SpawnNewGems(WorldData world);

// Generate internal grid as empty
WorldData GenerateEmpty(const int side, const std::vector<Gem::GemData>& gemData);

// Generate the entire grid picking randomly from gemData
WorldData GenerateFilled(const int side, const std::vector<Gem::GemData>& gemData);

// Checks for matches and returns a new world with maybe holes
WorldData RemoveGemsMatches(WorldData world);

// Moves gems down if there is a hole below
WorldData ApplyAnimation(WorldData world, const int pixelsPerFrame, const int textureSize);

// Returns true if the position can't be affected by gravity
bool IsPositionStable(const WorldData& world, const Vector2i position);

} // namespace World


inline bool operator==(const World::WorldData& A, const World::WorldData& B)
{
	return A.data == B.data;
}

inline bool operator!=(const World::WorldData& A, const World::WorldData& B)
{
	return A.data != B.data;
}