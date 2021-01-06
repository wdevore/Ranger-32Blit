#include <iostream>

#include "utilities.hpp"
#include "button.hpp"
#include "spout.hpp"
#include "ship.hpp"

// Forward declares
void draw_stats(uint32_t ms_start, uint32_t ms_end);

using namespace blit;

Ship ship;
Vec2 gravity;
uint32_t pTime = 0;
bool updateEnabled = true;

BlitButton MenuButton(Button::MENU);             // "2" on keyboard
BlitButton HomeButton(Button::HOME);             // "1" on keyboard
BlitButton AButton(Button::A);                   // "Z" on keyboard
BlitButton YButton(Button::Y);                   // "V" on keyboard
BlitButton DPAD_LEFTButton(Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
BlitButton DPAD_RIGHTButton(Button::DPAD_RIGHT); // "->" or "D" on keyboard.

Pen clearColor = {200, 200, 200};

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
    MenuButton.update();
    HomeButton.update();
    AButton.update();
    YButton.update();
    DPAD_LEFTButton.update();
    DPAD_RIGHTButton.update();

    if (MenuButton.pressed())
    {
        ship.destroy();
        exit(0);
    }

    if (HomeButton.tapped())
    {
        ship.reset();
        ship.debug();
    }

    // -----------------------------------------
    // Rotate
    if (DPAD_LEFTButton.pressed())
    {
        ship.rotateCCW();
    }
    else if (DPAD_RIGHTButton.pressed())
    {
        ship.rotateCW();
    }

    // -----------------------------------------
    // Thrust
    // Button::A == "Z" key
    ship.applyThrust(AButton.pressed());

    // Button::X = "C" key
    // if (pressed(Button::X))
    // {
    //     // std::cout << "X pressed" << std::endl;
    // }

    if (YButton.tapped())
    {
        updateEnabled = !updateEnabled;
    }

    if (updateEnabled)
        ship.update(dt, gravity);

    pTime = time;
}

// -----------------------------------------------------------------
// Render
// -----------------------------------------------------------------
void render(uint32_t time)
{
    uint32_t ms_start = now();

    screen.pen = clearColor;
    screen.clear();

    ship.render();

    uint32_t ms_end = now();

    // ******************************************************
    // Debug visuals. Remove in release mode.
    screen.pen = Pen(180, 180, 180);
    screen.line(Vec2(0, screen.bounds.h / 2), Vec2(screen.bounds.w, screen.bounds.h / 2));
    screen.line(Vec2(0, screen.bounds.h / 1.8), Vec2(screen.bounds.w, screen.bounds.h / 1.8));

    draw_stats(ms_start, ms_end);
    // ******************************************************
}
