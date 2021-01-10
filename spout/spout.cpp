#include <iostream>
#include <list>

#include "spout.hpp"
#include "game/game.hpp"

#include "game/defines.hpp"
#include "gui/button.hpp"
#include "game/ship.hpp"
#include "islands/island.hpp"
#include "islands/island_buffer.hpp"

namespace Game
{
    extern Ship ship; // Defined in game.cpp
    extern Vec2 gravity;
    extern Pen clearColor;

    Game::Button MenuButton(blit::Button::MENU);             // "2" on keyboard
    Game::Button HomeButton(blit::Button::HOME);             // "1" on keyboard
    Game::Button AButton(blit::Button::A);                   // "Z" on keyboard
    Game::Button YButton(blit::Button::Y);                   // "V" on keyboard
    Game::Button DPAD_LEFTButton(blit::Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
    Game::Button DPAD_RIGHTButton(blit::Button::DPAD_RIGHT); // "->" or "D" on keyboard.
    // Button::X = "C" key

    uint32_t pTime = 0;
    bool updateEnabled = true;

    // extern std::list<std::unique_ptr<IsLand>> islands;
    extern std::list<std::string> islandMap;

    extern State gameState;
    extern IslandBuffer buffer;

    // Forward declares
    void draw_stats(uint32_t ms_start, uint32_t ms_end);
} // namespace Game

using namespace blit;

// -----------------------------------------------------------------
// Intialize
// -----------------------------------------------------------------
void init()
{
    drand48(); // Prime RNG

    set_screen_mode(ScreenMode::hires);

    std::cout << "Dimesions: " << screen.bounds.w << " x " << screen.bounds.h << std::endl;

    using namespace Game;

    // auto island = std::make_unique<IsLand>(0);

    ship.init();

    buffer.clear();

    // islands.push_back(std::move(island));

    int xoff = 100;
    int yoff = 25;
    int x = 0;
    int y = 0;
    for (auto &row : Game::islandMap)
    {
        for (auto &c : row)
        {
            if (c == '1')
                buffer.setPixel(x + xoff, y + yoff);
            // std::cout << c;
            x++;
        }
        x = 0;
        y++;
        // std::cout << std::endl;
    }
}

// -----------------------------------------------------------------
// Update state
// -----------------------------------------------------------------
void update(uint32_t time)
{
    using namespace Game;

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

    if (YButton.tapped())
    {
        updateEnabled = !updateEnabled;
    }

    if (updateEnabled)
        ship.update(dt, gravity);

    if (ship.hitTripWire())
        buffer.scroll();

    bool collided = buffer.collide(ship);
    
    if (ship.isDead()) {
        ship.reset();
    }

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

    buffer.blit();

    ship.render();

    uint32_t ms_end = now();

    // ******************************************************
    // Debug visuals. Remove in release mode.
    // screen.pen = Pen(255, 127, 100);
    // screen.line(Vec2(0, Spout_ScrollLine), Vec2(screen.bounds.w, Spout_ScrollLine));

    Game::draw_stats(ms_start, ms_end);
    // ******************************************************
}
