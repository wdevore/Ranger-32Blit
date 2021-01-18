#include <iostream>

#include "../game/defines.hpp"
#include "island.hpp"

namespace Game
{
    extern float randF();

    IsLand::IsLand(int id)
    {
        this->id = id;
    }

    void IsLand::scroll()
    {
        // It's time to generate a new row of "pixels"

        // std::cout << "scrolling (" << id << ")" << std::endl;
        _scroll = true;
        shiftRate.adjust();
    }

    void IsLand::update(uint32_t time)
    {
        if (hCnt >= height)
        {
            reset();
            hCnt = 0;
            return;
        }

        shiftRate.update();
        // std::cout << shiftRate.iValue();
        hCnt++;
    }

    void IsLand::render()
    {
    }

    void IsLand::reset()
    {
        // Configure for another island by generating new values.
        height = 3 + int(randF() * 10);

        shiftRate.adjust();
    }
} // namespace Game