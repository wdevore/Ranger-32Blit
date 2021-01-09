#include <iostream>

#include "island_buffer.hpp"
#include "utilities.hpp"

namespace Game
{
    using namespace blit;
    extern Pen clearColor;

    IslandBuffer::IslandBuffer()
    {
    }

    void IslandBuffer::setRow(int row, std::vector<uint8_t> &cols)
    {
        int col = 0;
        for (auto &c : cols)
        {
            buffer[col][row] = c;
            col++;
        }
    }

    void IslandBuffer::setPixel(int x, int y)
    {
        buffer[x][y] = 1;
    }

    void IslandBuffer::clearPixel(int x, int y)
    {
        buffer[x][y] = 0;
    }

    void IslandBuffer::scroll()
    {
        for (int row = screen.bounds.h ; row >= 0; row--)
        {
            for (int col = 0; col < screen.bounds.w; col++)
            {
                buffer[col][row] = buffer[col][row-1];
            }
        }
    }

    void IslandBuffer::clear()
    {
        for (int row = 0; row < screen.bounds.h; row++)
        {
            for (int col = 0; col < screen.bounds.w; col++)
            {
                buffer[col][row] = 0;
            }
        }
    }

    void IslandBuffer::blit()
    {
        for (int row = 0; row < screen.bounds.h; row++)
        {
            for (int col = 0; col < screen.bounds.w; col++)
            {
                p.x = col;
                p.y = row;
                if (buffer[col][row] == 1)
                    screen.pen = colorSet;
                else
                    screen.pen = Game::clearColor;
                screen.pixel(p);
            }
        }
    }

} // namespace Game