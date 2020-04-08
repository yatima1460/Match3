#include <Game/World.hpp>

#include "gtest/gtest.h"



TEST(WorldTest, OneGemTypeWithMatchCreatesEmptyWorld)
{
    const std::vector<Gem::GemData> gems = {Gem::GemData("a")};
    const auto world = World::GenerateFilled(10,gems);
    const auto worldMatched = World::RemoveGemsMatches(world);

    EXPECT_EQ(world.data.size(), worldMatched.data.size());
    EXPECT_NE(world.data, worldMatched.data);
}

TEST(WorldTest, GenerateEmpty)
{
    const auto world = World::GenerateEmpty(10,{Gem::GemData("a")});
    
    for (int x = 0; x < world.side; x++)
    {
        for (int y = 0; y < world.side; y++)
        {
            EXPECT_EQ(world.data[x][y].drawingOffset.y, 0);
            EXPECT_TRUE(world.data[x][y].id.empty());
        }
    
    }
}


TEST(WorldTest, GenerateFilled)
{
    const auto world = World::GenerateFilled(10,{Gem::GemData("a")});
    
    for (int x = 0; x < world.side; x++)
    {
        for (int y = 0; y < world.side; y++)
        {
            EXPECT_EQ(world.data[x][y].drawingOffset.y, 0);
            EXPECT_EQ(world.data[x][y].id, "a");
        }
    
    }
}


// TEST(WorldTest, IsFilledWithGems)
// {
//     const auto worldFilled = World::GenerateFilled(100,{Gem::GemData("a")});
//     EXPECT_TRUE(World::IsStatic(worldFilled));
    
//     const auto worldEmpty = World::GenerateEmpty(100,{Gem::GemData("a")});
//     EXPECT_FALSE(World::IsStatic(worldEmpty));
// }


TEST(WorldTest, InvalidSide)
{
    ASSERT_DEATH(World::GenerateEmpty(-1,{Gem::GemData("a")}),".");
    ASSERT_DEATH(World::GenerateEmpty(0,{Gem::GemData("a")}),".");
    ASSERT_DEATH(World::GenerateEmpty(1,{Gem::GemData("a")}),".");
    ASSERT_DEATH(World::GenerateEmpty(2,{Gem::GemData("a")}),".");
    ASSERT_NO_FATAL_FAILURE(World::GenerateEmpty(3,{Gem::GemData("a")}));

}
