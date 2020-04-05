#include "World.hpp"

#include <cassert>

namespace World
{

// constexpr int GetIndex(const int x,const int y,const int side)
// {
//     return y*side + x;
// }

bool IsPositionStable(WorldData world, SDL_Point position)
{
   
    for (int y = position.y + 1; y < world.side; y++)
    {
        if (world.data[position.x][y].texture_name == "")
            return false;
    }

    return true;
    
}

WorldData Generate(const int side, const std::vector<Gem::GemData> gemData)
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

    // wd.data = new Gem::GemData *[side];
    // for (int i = 0; i < side; ++i)
    //     wd.data[i] = new Gem::GemData[side];

    for (int y = 0; y < side; y++)
    {
        for (int x = 0; x < side; x++)
        {
wd.data[x][y].texture_name = "";
            // int randNum = rand() % (gemData.size());
            // assert(randNum >= 0);
            // assert(randNum < (int)gemData.size());

            // wd.data[x][y] = gemData[randNum];
        }
    }

    return wd;
}

WorldData Swap(WorldData world, SDL_Point position1, SDL_Point position2)
{
    const auto gemPos1 = world.data[position1.x][position1.y];
    const auto gemPos2 = world.data[position2.x][position2.y];
    world.data[position1.x][position1.y] = gemPos2;
    world.data[position2.x][position2.y] = gemPos1;

    return world;
}

bool AllGemsFell(const WorldData world)
{
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y].IsFalling)
                return false;
        }
    }
    return true;
}

WorldData ApplyGravity(WorldData world)
{

    for (int y = 0; y < world.side - 1; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            // If below is empty
            if (world.data[x][y + 1].texture_name == "")
            {
                world.data[x][y].IsFalling = true;
                const int GRAVITY_SPEED = 8;
                world.data[x][y].drawingOffset.y += GRAVITY_SPEED;
                if (world.data[x][y].drawingOffset.y >= 64)
                {
                    world.data[x][y].drawingOffset.y = 0;
                    world.data[x][y + 1] = world.data[x][y];
                    world.data[x][y].texture_name = "";
                }
            }
            else
            {
               
               world.data[x][y].IsFalling = false;
            }
            
        }
    }

    // Ground line is always stable
    for (int x = 0; x < world.side; x++)
    {
        world.data[x][world.side-1].IsFalling = false;
    }

    return world;
}

WorldData SpawnNewGems(WorldData world)
{
    for (int x = 0; x < world.side; x++)
    {
        if (world.data[x][0].texture_name == "")
        {
            int randNum = rand() % (world.gemData.size());
            assert(randNum >= 0);
            assert(randNum < (int)world.gemData.size());

            world.data[x][0] = world.gemData[randNum];
            world.data[x][0].IsFalling = true;
        }
    }

    return world;
}

bool HasHoles(const WorldData world)
{
    return !IsFilledWithGems(world);
}

bool IsFilledWithGems(const WorldData world)
{
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y].texture_name == "")
            {
                return false;
            }
        }
    }
    return true;
}

WorldData RemoveGemsMatches(WorldData world)
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

            if (!World::IsPositionStable(world, {x,y}))
                continue;

            if (current.texture_name == next.texture_name && next.texture_name == nextnext.texture_name)
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

            if (!World::IsPositionStable(world, {x,y}))
                continue;

            if (current.texture_name == next.texture_name && next.texture_name == nextnext.texture_name)
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
                current_gem.texture_name = "";
            }
        }
    }

    return world;
}

} // namespace World
