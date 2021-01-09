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
        for (int row = screen.bounds.h; row >= 0; row--)
        {
            for (int col = 0; col < screen.bounds.w; col++)
            {
                buffer[col][row] = buffer[col][row - 1];
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

    bool IslandBuffer::collide(Ship &ship)
    {
        bool collided = pCollide(ship.posX(), ship.posY());
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = pCollide(ship.posX() - 1, ship.posY() + 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = pCollide(ship.posX() - 1, ship.posY() - 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = pCollide(ship.posX() + 1, ship.posY() - 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = pCollide(ship.posX() + 1, ship.posY() + 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        ship.setCollided(false);
        return false;
    }

    bool IslandBuffer::pCollide(int x, int y)
    {
        // Clip
        if (x < 0)
            x = 0;
        else if (x > screen.bounds.w - 1)
            x = screen.bounds.w - 1;

        if (y < 0)
            y = 0;
        else if (y > screen.bounds.h - 1)
            y = screen.bounds.h - 1;

        if (buffer[x][y] == 1)
        {
            // std::cout << "boom..... " << x << "," << y << std::endl;
            return true;
        }

        return false;
    }
} // namespace Game