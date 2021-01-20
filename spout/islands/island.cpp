#include <iostream>
#include <vector>

#include "../game/defines.hpp"
#include "island.hpp"

// An island moves closer to the view start position.
// Once it has done so the island is scrolled into view until the
// last line is scrolled.

namespace Game
{
    extern float randF();
    extern float lerp(float min, float max, float t);

    IsLand::IsLand(std::list<std::string> map)
    {
        this->map = map;
        height = map.size();
        reset();
    }

    void IsLand::update(uint32_t time, IslandBuffer &buffer)
    {
        buffer.scroll();
        // Clear top line from previous scroll
        buffer.clearLine(0);

        if (scrolling)
        {
            if (rIter == map.rend())
            {
                // std::cout << "island totally visible" << std::endl;
                // All lines have been copied into view
                scrolling = false;
                heightCnt = 0;
                reset();
            }
            else
            {
                // Copy a line from island map.
                std::string line = *rIter;
                // std::cout << "line: " << line << std::endl;
                // position the line horizontally
                int x = 0;
                for (auto &c : line)
                {
                    if (c == 'o')
                        buffer.setPixel(x + xoffset, 0);
                    x++;
                }

                ++rIter;
            }
        }
        else
        {
            // Currently the map is being "moved" closer to the view edge.
            if (distanceToView == 0)
            {
                // std::cout << "scrolling ready" << std::endl;
                // Now we are ready to start scrolling the map into view.
                scrolling = true;
                // Get an iterator that is positioned at the bottom of the island
                // because it is the bottom that appears first at the top of the screen.
                rIter = map.rbegin();
            }
            distanceToView--;
        }
    }

    void IsLand::reset()
    {
        // generate new distance
        distanceToView = int(lerp(50, 100, randF()));

        // generate horizontal offset
        xoffset = int(lerp(0, screen.bounds.w, randF()));
        // std::cout << "distanceToView: " << distanceToView << ", " << xoffset << std::endl;
    }
} // namespace Game