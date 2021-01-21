#include <iostream>
#include <vector>

#include "../game/defines.hpp"
#include "island.hpp"

// An island starts with a certain distance from the top of the screen.

namespace Game
{
    extern float randF();
    extern float lerp(float min, float max, float t);

    IsLand::IsLand(std::list<std::string> map)
    {
        this->map = map;
        reset();
    }

    void IsLand::update(uint32_t time, IslandBuffer &buffer)
    {
        if (scrolling)
        {
            if (rIter == map.rend())
            {
                // Island totally visible
                // All lines have been copied into view
                scrolling = false;
                reset();
            }
            else
            {
                // Copy a line from island map.
                // position the line horizontally
                int x = 0;
                for (auto &c : *rIter)
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