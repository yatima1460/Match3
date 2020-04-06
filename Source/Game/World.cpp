#include "World.hpp"
#include "Functional.hpp"
#include <cassert>

namespace World
{

CONST_FUNCTION bool IsPositionStable(const WorldData& world,const Vector2i position)
{

    for (int y = position.y + 1; y < world.side; y++)
    {
        if (world.data[position.x][y].id == "")
            return false;
    }

    return true;
}


CONST_FUNCTION WorldData GenerateFilled(const int side, const std::vector<Gem::GemData>& gemData)
{

    assert(side >= 3);
    assert(gemData.size() != 0);
    WorldData wd;

    wd.gemData = gemData;

    wd.side = side;

    wd.data.resize(side);
    for (int i = 0; i < side; i++)
    {
        wd.data[i].resize(side);
    }

    for (int y = 0; y < side; y++)
    {
        for (int x = 0; x < side; x++)
        {
            wd.data[x][y] = gemData[rand() % gemData.size()];
        }
    }

    return wd;
}

CONST_FUNCTION WorldData GenerateEmpty(const int side, const std::vector<Gem::GemData>& gemData)
{
    assert(side >= 3);
    assert(gemData.size() != 0);
    WorldData wd;

    wd.gemData = gemData;
    wd.side = side;

    wd.data.resize(side);
    for (int i = 0; i < side; i++)
        wd.data[i].resize(side);

    return wd;
}

CONST_FUNCTION WorldData Swap(WorldData world, Vector2i position1, Vector2i position2)
{
    const auto gemPos1 = world.data[position1.x][position1.y];
    const auto gemPos2 = world.data[position2.x][position2.y];
    world.data[position1.x][position1.y] = gemPos2;
    world.data[position2.x][position2.y] = gemPos1;

    return world;
}

CONST_FUNCTION WorldData ApplyGravity(WorldData world, const int pixelsPerFrame, const int textureSize)
{

    for (int y = 0; y < world.side - 1; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            // If below is empty
            if (world.data[x][y + 1].id == "")
            {

                world.data[x][y].drawingOffset.y += pixelsPerFrame;
                if (world.data[x][y].drawingOffset.y >= textureSize)
                {
                    world.data[x][y].drawingOffset.y = 0;
                    world.data[x][y + 1] = world.data[x][y];
                    world.data[x][y].id = "";
                }
            }
        }
    }

    return world;
}

CONST_FUNCTION WorldData SpawnNewGems(WorldData world)
{
    for (int x = 0; x < world.side; x++)
    {
        if (world.data[x][0].id == "")
        {
            int randNum = rand() % (world.gemData.size());
            assert(randNum >= 0);
            assert(randNum < (int)world.gemData.size());

            world.data[x][0] = world.gemData[randNum];
        }
    }

    return world;
}

CONST_FUNCTION bool HasHoles(const WorldData& world)
{
    return !IsFilledWithGems(world);
}

CONST_FUNCTION bool IsFilledWithGems(const WorldData& world)
{
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y].id == "")
            {
                return false;
            }
        }
    }
    return true;
}

CONST_FUNCTION WorldData RemoveGemsMatches(WorldData world) 
{
    std::vector<std::vector<bool>> toRemove;
    toRemove.resize(world.side);
    for (int i = 0; i < world.side; i++)
        toRemove[i].resize(world.side);

    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            toRemove[x][y] = false;
        }
    }

    // Remove horizontal matches
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side - 2; x++)
        {
            const auto current = world.data[x][y];
            const auto next = world.data[x + 1][y];
            const auto nextnext = world.data[x + 2][y];

            if (!World::IsPositionStable(world, {x, y}))
                continue;

            if (current.id == next.id && next.id == nextnext.id)
            {
                toRemove[x][y] = true;
                toRemove[x + 1][y] = true;
                toRemove[x + 2][y] = true;
            }
        }
    }

    // Remove vertical matches
    for (int x = 0; x < world.side; x++)
    {
        for (int y = 0; y < world.side - 2; y++)
        {

            const auto current = world.data[x][y];
            const auto next = world.data[x][y + 1];
            const auto nextnext = world.data[x][y + 2];

            if (!World::IsPositionStable(world, {x, y}))
                continue;

            if (current.id == next.id && next.id == nextnext.id)
            {
                toRemove[x][y] = true;
                toRemove[x][y + 1] = true;
                toRemove[x][y + 2] = true;
            }
        }
    }

    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {

            if (toRemove[x][y])
            {
                auto &current_gem = world.data[x][y];
                current_gem.id = "";
            }
        }
    }

    return world;
}

} // namespace World
