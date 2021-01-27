#pragma once

#include "32blit.hpp"

#include "../game/ship.hpp"
#include "../particles/particle_node.hpp"
#include "../particles/particle_system.hpp"

// Note: This buffer holds more than just Islands.

namespace Game
{
    using namespace blit;

    // Same size as display. 320x240
    class IslandBuffer
    {
    private:
        //           320
        //   .---------------------.
        //   |                     |
        //   |                     |
        //   |                     |  240
        //   |                     |
        //   |                     |
        //   .---------------------.
        //
        //             col  row
        uint8_t buffer[320][240]{};
        Pen islandColor = {64, 64, 64};
        Pen mineColor = {255, 127, 0};
        Point p;

    public:
        IslandBuffer() = default;

        void setRow(int y, std::vector<uint8_t> &cols);
        void setPixel(int x, int y);
        void setPixel(int x, int y, uint8_t v);
        void clearPixel(int x, int y);

        void scroll();
        void clearLine(int line);
        void clear();
        void blit();

        void clip(int &x, int &y);

        int collide(Ship &ship);
        int collide(int x, int y);
        int collide(ParticleSystem &ps);
        int collide(std::unique_ptr<ParticleNode> &p);

    private:
        void clearSquare(int &count, std::unique_ptr<ParticleNode> &p);
    };

} // namespace Game