#include <iostream>

#include "../game/defines.hpp"
#include "island_buffer.hpp"

namespace Game
{
    using namespace blit;
    extern Pen clearColor;

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
        else if (x > screen.bounds.w - 1)
            x = screen.bounds.w - 1;

        if (y < 0)
            y = 0;
        else if (y > screen.bounds.h - 1)
            y = screen.bounds.h - 1;
    }

    int IslandBuffer::collide(Ship &ship)
    {
        // Instead of performing a complete pixel perfect collision, I simply
        // test the corners of a square and its center point. It looks convincing enough.

        int collided = collide(ship.posX(), ship.posY());
        if (collided > 0)
        {
            ship.setCollided(collided);
            return collided;
        }

        collided = collide(ship.posX() - 1, ship.posY() + 1);
        if (collided > 0)
        {
            ship.setCollided(collided);
            return collided;
        }

        collided = collide(ship.posX() - 1, ship.posY() - 1);
        if (collided > 0)
        {
            ship.setCollided(collided);
            return collided;
        }

        collided = collide(ship.posX() + 1, ship.posY() - 1);
        if (collided > 0)
        {
            ship.setCollided(collided);
            return collided;
        }

        collided = collide(ship.posX() + 1, ship.posY() + 1);
        if (collided > 0)
        {
            ship.setCollided(collided);
            return collided;
        }

        ship.setCollided(0);

        int count = collide(ship.particleThrust());

        ship.addToScore(count);

        return 0;
    }

    int IslandBuffer::collide(std::unique_ptr<ParticleNode> &p)
    {
        int collided = collide(p->posX(), p->posY());
        p->setCollided(collided > 0);

        if (collided > 0)
        {
            return collided;
        }

        return 0;
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
                    // Does the particle collide with something in the buffer
                    int colidId = collide(p);

                    if (colidId == 1)
                    {
                        clearSquare(count, p, 1);
                    }
                    else if (colidId == 2)
                    {
                        // The particle collided with a mine.
                        // Was the particle from the mine exploder?
                        if (ps.Id() == 2)
                        {
                            clearSquare(count, p, 2);
                        }
                    }
                }
            }
        }

        return count;
    }

    void IslandBuffer::clearSquare(int &count, std::unique_ptr<ParticleNode> &p, int id)
    {
        count++;
        p->setActive(false);

        // Clear a total of 9 pixels.
        int x = p->posX();
        int y = p->posY();

        clip(x, y);
        if (buffer[x][y] == id)
            buffer[x][y] = 0;

        int xm1 = x - 1;
        int xp1 = x + 1;
        int ym1 = y - 1;
        int yp1 = y + 1;
        clip(xm1, ym1);
        clip(xp1, yp1);

        if (buffer[xm1][ym1] == id)
            buffer[xm1][ym1] = 0;
        if (buffer[xp1][yp1] == id)
            buffer[xp1][yp1] = 0;
        if (buffer[xm1][yp1] == id)
            buffer[xm1][yp1] = 0;
        if (buffer[xp1][ym1] == id)
            buffer[xp1][ym1] = 0;
        if (buffer[xm1][y] == id)
            buffer[xm1][y] = 0;
        if (buffer[xp1][y] == id)
            buffer[xp1][y] = 0;
        if (buffer[x][yp1] == id)
            buffer[x][yp1] = 0;
        if (buffer[x][ym1] == id)
            buffer[x][ym1] = 0;
    }

    int IslandBuffer::collide(int x, int y)
    {
        // Clip
        clip(x, y);

        if (buffer[x][y] > 0)
        {
            return buffer[x][y];
        }

        return 0;
    }
} // namespace Game