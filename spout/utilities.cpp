#include <iostream>

#include "32blit.hpp"

using namespace blit;

void draw_stats(uint32_t ms_start, uint32_t ms_end)
{
    // -----------------------------------
    // draw FPS meter
    // -----------------------------------
    int block_size = 6;
    for (uint32_t i = 0; i < (ms_end - ms_start); i++)
    {
        screen.pen = Pen(i * 5, 255 - (i * 5), 0);
        screen.rectangle(Rect(i * (block_size + 1) + 1 + 13, screen.bounds.h - block_size - 1, block_size, block_size));
    }

    screen.alpha = 255;
    screen.pen = Pen(255, 255, 255, 100);
    screen.rectangle(Rect(1, screen.bounds.h - 10, 12, 9));
    screen.pen = Pen(255, 255, 255, 200);
    std::string fms = std::to_string(ms_end - ms_start);
    screen.text(fms, minimal_font, Rect(3, screen.bounds.h - 9, 10, 16));
}