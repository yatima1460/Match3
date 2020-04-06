#include <World.hpp>

#include "gtest/gtest.h"



TEST(WorldTest, OneGemTypeWithMatchCreatesEmptyWorld)
{
    const std::vector<Gem::GemData> gems = {{"a"}};
    const auto world = World::GenerateFilled(10,gems);
    const auto worldMatched = World::RemoveGemsMatches(world);

    EXPECT_EQ(world.data.size(), worldMatched.data.size());
    EXPECT_NE(world.data, worldMatched.data);
}

TEST(WorldTest, GenerateEmpty)
{
    const auto world = World::GenerateEmpty(10,{{"a"}});
    
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
    const auto world = World::GenerateFilled(10,{{"a"}});
    
    for (int x = 0; x < world.side; x++)
    {
        for (int y = 0; y < world.side; y++)
        {
            EXPECT_EQ(world.data[x][y].drawingOffset.y, 0);
            EXPECT_EQ(world.data[x][y].id, "a");
        }
    
    }
}


TEST(WorldTest, IsFilledWithGems)
{
    const auto worldFilled = World::GenerateFilled(100,{{"a"}});
    EXPECT_TRUE(World::IsFilledWithGems(worldFilled));
    
    const auto worldEmpty = World::GenerateEmpty(100,{{"a"}});
    EXPECT_FALSE(World::IsFilledWithGems(worldEmpty));
}


TEST(WorldTest, InvalidSide)
{
    ASSERT_DEATH(World::GenerateEmpty(-1,{{"a"}}),".");
    ASSERT_DEATH(World::GenerateEmpty(0,{{"a"}}),".");
    ASSERT_DEATH(World::GenerateEmpty(1,{{"a"}}),".");
    ASSERT_DEATH(World::GenerateEmpty(2,{{"a"}}),".");
    ASSERT_NO_FATAL_FAILURE(World::GenerateEmpty(3,{{"a"}}));

}
