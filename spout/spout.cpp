#include <iostream>

#include "utilities.hpp"
#include "spout.hpp"
#include "ship.hpp"

// Forward declares
void draw_stats(uint32_t ms_start, uint32_t ms_end);

using namespace blit;

Ship ship;
Vec2 gravity;
uint32_t pTime = 0;

// -----------------------------------------------------------------
// Intialize
// -----------------------------------------------------------------
void init()
{
    set_screen_mode(ScreenMode::hires);

    ship.init();

    gravity.x = 0.0;
    gravity.y = GravityAcceleration;
}

// -----------------------------------------------------------------
// Update state
// -----------------------------------------------------------------
void update(uint32_t time)
{
    uint32_t dt = time - pTime;
    // std::cout << "update: " << time << ", dt: " << dt << std::endl;

    // "2" on keyboard
    if (pressed(Button::MENU))
    {
        ship.destroy();
        exit(0);
    }

    // "1" on keyboard
    if (pressed(Button::HOME))
    {
        ship.reset();
        ship.debug();
    }

    // -----------------------------------------
    // Rotate
    if (pressed(Button::DPAD_LEFT)) // "A" key
    {
        ship.rotateCCW();
    }
    else if (pressed(Button::DPAD_RIGHT))
    {
        ship.rotateCW();
    }

    // -----------------------------------------
    // Thrust
    // Button::A == "Z" key
    ship.applyThrust(pressed(Button::A));

    ship.update(dt, gravity);

    pTime = time;
}

// -----------------------------------------------------------------
// Render
// -----------------------------------------------------------------
void render(uint32_t time)
{
    uint32_t ms_start = now();

    screen.pen = Pen(200, 200, 200);
    screen.clear();

    ship.render();

    uint32_t ms_end = now();

    draw_stats(ms_start, ms_end);
}
