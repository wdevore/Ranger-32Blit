#include <iostream>

#include "utilities.hpp"
#include "button.hpp"
#include "spout.hpp"
#include "ship.hpp"

// Forward declares
void draw_stats(uint32_t ms_start, uint32_t ms_end);

using namespace blit;

namespace Game
{
    Ship ship;
    Vec2 gravity;

    Game::Button MenuButton(blit::Button::MENU);             // "2" on keyboard
    Game::Button HomeButton(blit::Button::HOME);             // "1" on keyboard
    Game::Button AButton(blit::Button::A);                   // "Z" on keyboard
    Game::Button YButton(blit::Button::Y);                   // "V" on keyboard
    Game::Button DPAD_LEFTButton(blit::Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
    Game::Button DPAD_RIGHTButton(blit::Button::DPAD_RIGHT); // "->" or "D" on keyboard.
    // Button::X = "C" key

    Pen clearColor = {200, 200, 200};

} // namespace Game

uint32_t pTime = 0;
bool updateEnabled = true;

// -----------------------------------------------------------------
// Intialize
// -----------------------------------------------------------------
void init()
{
    set_screen_mode(ScreenMode::hires);

    using namespace Game;

    ship.init();

    gravity.x = 0.0;
    gravity.y = GravityAcceleration;
}

// -----------------------------------------------------------------
// Update state
// -----------------------------------------------------------------
void update(uint32_t time)
{
    using namespace Game;

    uint32_t dt = time - pTime;
    
    // std::cout << "update: " << time << ", dt: " << dt << std::endl;
    Game::MenuButton.update();
    Game::HomeButton.update();
    Game::AButton.update();
    Game::YButton.update();
    Game::DPAD_LEFTButton.update();
    Game::DPAD_RIGHTButton.update();

    if (Game::MenuButton.pressed())
    {
        ship.destroy();
        exit(0);
    }

    if (Game::HomeButton.tapped())
    {
        ship.reset();
        ship.debug();
    }

    // -----------------------------------------
    // Rotate
    if (Game::DPAD_LEFTButton.pressed())
    {
        ship.rotateCCW();
    }
    else if (Game::DPAD_RIGHTButton.pressed())
    {
        ship.rotateCW();
    }

    // -----------------------------------------
    // Thrust
    // Button::A == "Z" key
    ship.applyThrust(Game::AButton.pressed());

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
    using namespace Game;

    uint32_t ms_start = now();

    screen.pen = clearColor;
    screen.clear();

    ship.render();

    uint32_t ms_end = now();

    // ******************************************************
    // Debug visuals. Remove in release mode.
    screen.pen = Pen(180, 180, 180);
    screen.line(Vec2(0, ScrollLine), Vec2(screen.bounds.w, ScrollLine));

    draw_stats(ms_start, ms_end);
    // ******************************************************
}
