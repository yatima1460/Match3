#include "World.hpp"

#include <cassert>

namespace World
{

// constexpr int GetIndex(const int x,const int y,const int side)
// {
//     return y*side + x;
// }

WorldData Generate(int side, std::vector<Gem::GemData> gemData)
{
    //srand(time(NULL));
    assert(side >= 3);
    assert(gemData.size() != 0);
    WorldData wd;

    wd.side = side;

    wd.data = new Gem::GemData *[side];
    for (int i = 0; i < side; ++i)
        wd.data[i] = new Gem::GemData[side];

    for (int y = 0; y < side; y++)
    {
        for (int x = 0; x < side; x++)
        {

            int randNum = rand() % (gemData.size());
            assert(randNum >= 0);
            assert(randNum < (int)gemData.size());

            wd.data[x][y] = gemData[randNum];
        }
    }

    return wd;
}

WorldData RemoveMatches(WorldData world)
{

    bool **toRemove = new bool *[world.side];
    for (int i = 0; i < world.side; ++i)
        toRemove[i] = new bool[world.side];

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
            const auto next = world.data[x][y+1];
            const auto nextnext = world.data[x][y+2];

            if (current.texture_name == next.texture_name && next.texture_name == nextnext.texture_name)
            {
                toRemove[x][y] = true;
                toRemove[x][y+1] = true;
                toRemove[x][y+2] = true;
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

    delete[] toRemove;

    return world;
}

} // namespace World
