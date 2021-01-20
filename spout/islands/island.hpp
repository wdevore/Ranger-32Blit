#pragma once

#include <list>

#include "32blit.hpp"
#include "island_buffer.hpp"

using namespace blit;

// An island scrolls in from the top of the display.
// It begins to appears when the off screen distance reaches zero.

namespace Game
{
    class IsLand
    {
    private:
        // int mapIdx = 0;

        Pen color = {64, 64, 64};
        bool scrolling = false;
        int heightCnt;
        int height;

        int distanceToView = 0;
        int xoffset = 50;
        std::list<std::string> map;
        std::list<std::string>::reverse_iterator rIter;

    public:
        IsLand(std::list<std::string>);

        void reset();

        void update(uint32_t time, IslandBuffer &buffer);
    };

} // namespace Game