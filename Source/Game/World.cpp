#include "World.hpp"

#include <cassert>

namespace World
{

  WorldData Generate(size_t side, std::vector<Gem::GemData> gemData)
    {
        WorldData wd;

        wd.side = side;

        assert(side != 0);
        assert(gemData.size() != 0);
        
        for (size_t x = 0; x < side; x++)
        {
            for (size_t y = 0; y < side; y++)
            {
                int randNum = rand() % (gemData.size());
                assert(randNum >= 0);
                assert(randNum < (int)gemData.size());
                wd.data.push_back(gemData[randNum]);
            }
        }

        return wd;

    }


}
