#include <iostream>
#include <vector>

#include "../game/defines.hpp"
#include "mine.hpp"

namespace Game
{
    extern float randF();
    extern float lerp(float min, float max, float t);

    Mine::Mine(std::list<std::string> map)
    {
        this->map = map;
        reset();
    }

    void Mine::update(uint32_t time, IslandBuffer &buffer)
    {
        if (scrolling)
        {
            if (fIter == map.end())
            {
                // mine is compeletly visible
                // All lines have been copied into view
                scrolling = false;
                reset();
            }
            else
            {
                // Copy a line from the map.
                // position the line horizontally
                int x = 0;
                for (auto &c : *fIter)
                {
                    if (c == 'o')
                        buffer.setPixel(x + xoffset, 0, 2);
                    x++;
                }

                ++fIter;
            }
        }
        else
        {
            // Currently the map is being "moved" closer to the view edge.
            if (distanceToView == 0)
            {
                // Now we are ready to start scrolling the map into view.
                scrolling = true;

                // Get an iterator that is positioned at the bottom of the map
                // because it is the bottom that appears first at the top of the screen.
                fIter = map.begin();
            }
            distanceToView--;
        }
    }

    void Mine::reset()
    {
        // generate new distance
        distanceToView = int(lerp(MineVerticalDistToViewMin, MineVerticalDistToViewMax, randF()));

        // generate horizontal offset
        xoffset = int(lerp(MineXOffsetMin, screen.bounds.w - MineXOffsetMax, randF()));
    }

} // namespace Game