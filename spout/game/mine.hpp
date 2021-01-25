#pragma once

#include <list>

#include "../islands/island_buffer.hpp"

namespace Game
{
    class Mine
    {
    private:
        Pen color = {64, 64, 64};
        bool scrolling = false;

        int distanceToView = 0;
        int xoffset = 50;

        std::list<std::string> map;
        std::list<std::string>::iterator fIter;

    public:
        Mine(std::list<std::string> map);

        void reset();

        void update(uint32_t time, IslandBuffer &buffer);
    };

} // namespace Game