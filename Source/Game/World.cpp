#include "Game/World.hpp"
#include "Functional.hpp"
#include <cassert>
#include "Math/Vector2f.hpp"

namespace World
{

CONST_FUNCTION bool IsPositionStable(const WorldData &world, const Vector2i position)
{

    for (int y = position.y + 1; y < world.side; y++)
    {
        if (world.data[position.x][y].id.empty())
            return false;
    }

    return true;
}

CONST_FUNCTION WorldData GenerateFilled(const int side, const std::vector<Gem::GemData> &gemData)
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

CONST_FUNCTION WorldData GenerateEmpty(const int side, const std::vector<Gem::GemData> &gemData)
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

CONST_FUNCTION WorldData Swap(WorldData world, const Vector2i &position1, const Vector2i &position2)
{
    const auto gemPos1 = world.data[position1.x][position1.y];
    const auto gemPos2 = world.data[position2.x][position2.y];
    world.data[position1.x][position1.y] = gemPos2;
    world.data[position2.x][position2.y] = gemPos1;

    return world;
}

CONST_FUNCTION WorldData CalculateGravity(WorldData world)
{
    for (int y = 0; y < world.side - 1; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y + 1].id.empty())
            {
                world.data[x][y].animation = Gem::GemState::FALLING;
                world.data[x][y].drawingOffsetGoal = {0, 64};
            }
        }
    }
    return world;
}

CONST_FUNCTION WorldData ApplyAnimation(WorldData world, const int pixelsPerFrame, const int textureSize)
{

    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            auto &currentGem = world.data[x][y];

            if (currentGem.id.empty())
                continue;
            if (Vector2f::distance(currentGem.drawingOffset, currentGem.drawingOffsetGoal) > 0.25f)
            {
                auto vectorPointing = currentGem.drawingOffsetGoal - currentGem.drawingOffset;
                vectorPointing = Vector2f::normalize(vectorPointing);
                vectorPointing *= pixelsPerFrame;
                currentGem.drawingOffset += vectorPointing;
            }
            else
            {
                // if animation is completed
                switch (currentGem.animation)
                {

                case Gem::GemState::FALLING:
                {
                    if (y != world.side - 1)
                    {
                        auto &belowGem = world.data[x][y + 1];
                        belowGem = currentGem;
                        belowGem.animation = Gem::GemState::ANIMATION_DONE;
                        belowGem.drawingOffset = {0, 0};
                        belowGem.drawingOffsetGoal = {0, 0};

                        world.data[x][y].id = "";
                    }

                    break;

                default:
                    break;
                }
                }
            }
        }
    }

    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y].animation == Gem::GemState::ANIMATION_DONE)
                world.data[x][y].animation = Gem::GemState::STATIC;
        }
    }

    return world;
}

CONST_FUNCTION WorldData SpawnNewGems(WorldData world)
{
    for (int x = 0; x < world.side; x++)
    {
        if (world.data[x][0].id.empty())
        {
            int randNum = rand() % (world.gemData.size());
            assert(randNum >= 0);
            assert(randNum < (int)world.gemData.size());
            world.data[x][0] = world.gemData[randNum];
        }
    }

    return world;
}

CONST_FUNCTION bool IsStatic(const WorldData &world)
{
    for (int y = 0; y < world.side; y++)
    {
        for (int x = 0; x < world.side; x++)
        {
            if (world.data[x][y].animation != Gem::GemState::STATIC)
                return false;
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

            if (current.animation == Gem::GemState::STATIC && next.animation == Gem::GemState::STATIC && nextnext.animation == Gem::GemState::STATIC && current.id == next.id && next.id == nextnext.id)
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

            if (current.animation == Gem::GemState::STATIC && next.animation == Gem::GemState::STATIC && nextnext.animation == Gem::GemState::STATIC && current.id == next.id && next.id == nextnext.id)
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
