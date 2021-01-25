#include <iostream>

#include "../game/defines.hpp"
#include "island_buffer.hpp"

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
            clip(col, row);

            buffer[col][row] = c;
            col++;
        }
    }

    void IslandBuffer::setPixel(int x, int y)
    {
        clip(x, y);
        buffer[x][y] = 1;
    }

    void IslandBuffer::setPixel(int x, int y, uint8_t v)
    {
        clip(x, y);
        buffer[x][y] = v;
    }

    void IslandBuffer::clearPixel(int x, int y)
    {
        clip(x, y);
        buffer[x][y] = 0;
    }

    void IslandBuffer::scroll()
    {
        for (int row = screen.bounds.h - 1; row > 0; row--)
        {
            for (int col = 0; col < screen.bounds.w; col++)
            {
                buffer[col][row] = buffer[col][row - 1];
            }
        }
    }

    void IslandBuffer::clearLine(int line)
    {
        for (int col = 0; col < screen.bounds.w; col++)
        {
            buffer[col][line] = 0;
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
                    screen.pen = islandColor;
                else if (buffer[col][row] == 2)
                    screen.pen = mineColor;
                else
                    screen.pen = Game::clearColor;
                screen.pixel(p);
            }
        }
    }

    void IslandBuffer::clip(int &x, int &y)
    {
        if (x < 0)
            x = 0;
        else if (x > 319)
            x = 319;

        if (y < 0)
            y = 0;
        else if (y > 239)
            y = 239;
    }

    bool IslandBuffer::collide(Ship &ship)
    {
        // Instead of performing a complete pixel perfect collision, I simply
        // test the corners of a square and its center point. It looks convincing enough.

        bool collided = collide(ship.posX(), ship.posY());
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = collide(ship.posX() - 1, ship.posY() + 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = collide(ship.posX() - 1, ship.posY() - 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = collide(ship.posX() + 1, ship.posY() - 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        collided = collide(ship.posX() + 1, ship.posY() + 1);
        if (collided)
        {
            ship.setCollided(true);
            return collided;
        }

        ship.setCollided(false);

        int count = collide(ship.particleThrust());
        ship.addToScore(count);

        return false;
    }

    bool IslandBuffer::collide(std::unique_ptr<ParticleNode> &p)
    {
        bool collided = collide(p->posX(), p->posY());
        p->setCollided(collided);
        if (collided)
        {
            return collided;
        }
        return false;
    }

    int IslandBuffer::collide(ParticleSystem &ps)
    {
        int count = 0;

        if (ps.isActive())
        {
            int x = 0;
            int y = 0;
            int xm1 = 0;
            int xp1 = 0;
            int ym1 = 0;
            int yp1 = 0;
            for (auto &p : ps.getParticles())
            {
                if (p->isActive())
                {
                    if (collide(p))
                    {
                        count++;
                        p->setActive(false);

                        // Clear a total of 9 pixels.
                        x = p->posX();
                        y = p->posY();
                        clip(x, y);
                        buffer[x][y] = 0;

                        xm1 = x - 1;
                        xp1 = x + 1;
                        ym1 = y - 1;
                        yp1 = y + 1;
                        clip(xm1, ym1);
                        clip(xp1, yp1);

                        buffer[xm1][ym1] = 0;
                        buffer[xp1][yp1] = 0;
                        buffer[xm1][yp1] = 0;
                        buffer[xp1][ym1] = 0;
                        buffer[xm1][y] = 0;
                        buffer[xp1][y] = 0;
                        buffer[x][yp1] = 0;
                        buffer[x][ym1] = 0;
                    }
                }
            }
        }

        return count;
    }

    bool IslandBuffer::collide(int x, int y)
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
            return true;
        }

        return false;
    }
} // namespace Game