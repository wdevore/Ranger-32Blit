#include <iostream>
#include <list>
#include <vector>

#include "../game/mine.hpp"
#include "mines.hpp"

namespace Game
{
    void Mines::update(uint32_t time, IslandBuffer &buffer)
    {
        // buffer.scroll();
        // // Clear top line from previous scroll
        // buffer.clearLine(0);

        for (auto &mine : mines)
        {
            mine->update(time, buffer);
        }
    }

    void Mines::render()
    {
    }

    void Mines::addMine(std::unique_ptr<Mine> map)
    {
        mines.push_back(std::move(map));
    }
} // namespace Game