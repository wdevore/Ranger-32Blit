#pragma once

#include <list>

#include "island_buffer.hpp"

// An island scrolls in from the top of the display.
// It begins to appears when the off screen distance reaches zero.

namespace Game
{
    class IsLand
    {
    private:
        Pen color = {64, 64, 64};
        bool scrolling = false;
        int scrollDirection = 0; // 0 = forward, 1 = reverse
        
        int distanceToView = 0;
        int xoffset = 50;
        std::list<std::string> map;

        bool iteratorType = false;
        // Iterator to show island bottom to top
        std::list<std::string>::reverse_iterator rIter;
        // Iterator to show island upside down.
        std::list<std::string>::iterator fIter;

    public:
        IsLand(std::list<std::string>);

        void reset();

        void update(uint32_t time, IslandBuffer &buffer);

    private:
        void scrollForward(IslandBuffer &buffer);
        void scrollReverse(IslandBuffer &buffer);
    };

} // namespace Game