#include <iostream>
#include <sstream>

#include "scene_game.hpp"
#include "../scenes/scene_manager.hpp"

#define PRECISION 8

namespace Game
{
    extern int pitch;
    extern uint32_t pixels[320 * 240];

    // "Top" & "bottom" is relative to the triangle
    void ddaFlatBottom(int64_t topX, int64_t topY, int64_t bottomLeftX, int64_t bottomRightX, int64_t bottomY)
    {
        int64_t x = topX << PRECISION;
        int64_t w = 0 << PRECISION;
        int64_t addendX = ((bottomLeftX - topX) << PRECISION) / (bottomY - topY);
        int64_t addendW = ((bottomRightX - bottomLeftX) << PRECISION) / (bottomY - topY);

        for (int y = topY; y <= bottomY; y++)
        {
            uintptr_t offset = pitch * y + 4 * (x >> PRECISION);
            uint32_t *ptr = (uint32_t *)(pixels + offset);
            for (int i = 0; i < (w >> PRECISION); i++)
            {
                ptr[i] = 0xFF0000FF;
            }

            x += addendX;
            w += addendW;
        }
    }

    void ddaFlatTop(int64_t topX, int64_t topY, int64_t bottomLeftX, int64_t bottomRightX, int64_t bottomY)
    {
        int64_t x = topX << PRECISION;
        int64_t w = 0 << PRECISION;
        int64_t addendX = ((bottomLeftX - topX) << PRECISION) / (topY - bottomY);
        int64_t addendW = ((bottomRightX - bottomLeftX) << PRECISION) / (topY - bottomY);

        for (int y = topY; y >= bottomY; y--)
        {
            uintptr_t offset = pitch * y + 4 * (x >> PRECISION);
            uint32_t *ptr = (uint32_t *)(pixels + offset);
            for (int i = 0; i < (w >> PRECISION); i++)
            {
                ptr[i] = 0xFF0000FF;
            }

            x += addendX;
            w += addendW;
        }
    }

    void drawTriangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3)
    {
        // Bubble-sort vertices in ascending Y order.
        // While this would be necessary in the general case, we can remove this if we limit our level design in certain ways,
        // and limit the camera orientation in-game
        if (y3 < y2)
        {
            int64_t temp = y2;
            y2 = y3;
            y3 = temp;

            temp = x2;
            x2 = x3;
            x3 = temp;
        }
        if (y2 < y1)
        {
            int64_t temp = y1;
            y1 = y2;
            y2 = temp;

            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y3 < y2)
        {
            int64_t temp = y2;
            y2 = y3;
            y3 = temp;

            temp = x2;
            x2 = x3;
            x3 = temp;
        }

        if (y1 == y2)
        {
            ddaFlatTop(x3, y3, x1, x2, y1);
        }
        else if (y2 == y3)
        {
            ddaFlatBottom(x1, y1, x2, x3, y2);
        }
        else
        {
            int64_t x4 = x1 + ((((x3 - x1) << PRECISION) / (y3 - y1) * (y2 - y1)) >> PRECISION);

            if (x4 < x2)
            {
                int64_t temp = x4;
                x4 = x2;
                x2 = temp;
            }

            ddaFlatBottom(x1, y1, x2, x4, y2);
            ddaFlatTop(x3, y3, x2, x4, y2);
        }
    }

} // namespace Game
