#include <iostream>
#include <list>
#include <vector>

#include "island.hpp"
#include "islands.hpp"

namespace Game
{
    extern std::vector<std::list<std::string>> islandMaps;

    void IsLands::update(uint32_t time, IslandBuffer &buffer)
    {
        buffer.scroll();
        // Clear top line from previous scroll
        buffer.clearLine(0);

        for (auto &island : islands)
        {
            island.update(time, buffer);
        }
    }

    void IsLands::render()
    {
    }

    void IsLands::init(int seed)
    {
        int idx = 0;
        for (auto &island : islandMaps)
        {
            IsLand isl(islandMaps[idx]);
            islands.push_back(isl);
            idx++;
            // break;
        }

        islandMaps.clear();
    }
} // namespace Game