#include <iostream>

#include "island.hpp"

namespace Game
{
    IsLand::IsLand(int id)
    {
        this->id = id;
        color = {64, 64, 64};
        _scroll = false;
    }

    void IsLand::scroll()
    {
        std::cout << "scrolling (" << id << ")" << std::endl;
        _scroll = true;
    }

    void IsLand::update(uint32_t time)
    {
        // If a scroll occurred then generate new values for creating a new line.
        if (_scroll)
        {
            _scroll = false;
        }
    }

    void IsLand::render()
    {
    }

} // namespace Game