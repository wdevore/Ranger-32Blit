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
        for (auto &island : islands)
        {
            island.update(time, buffer);
        }
    }

    void IsLands::render()
    {
    }

    void IsLands::reset(int seed)
    {
        for (auto &island : islandMaps)
        {
            IsLand isl(islandMaps[seed]);
            islands.push_back(isl);
            break;
        }

        islandMaps.clear();

        // int xoff = 50;
        // int yoff = 50;
        // int x = 0;
        // int y = 0;
        // for (auto &row : Game::islandMaps[3])
        // {
        //     for (auto &c : row)
        //     {
        //         if (c == 'o')
        //             buffer.setPixel(x + xoff, y + yoff);
        //         x++;
        //     }
        //     x = 0;
        //     y++;
        // }
    }
} // namespace Game