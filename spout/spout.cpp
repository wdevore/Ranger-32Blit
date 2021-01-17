#include <iostream>
#include <list>

#include "engine/api_private.hpp"
#include "spout.hpp"
#include "game/game.hpp"

#include "game/defines.hpp"
#include "gui/button.hpp"
#include "scenes/scene_manager.hpp"

#include "scenes/scene_boot.hpp"
#include "scenes/scene_splash.hpp"
#include "scenes/scene_game.hpp"
#include "scenes/scene_exit.hpp"
#include "scenes/scene_menu.hpp"

using namespace blit;

namespace Game
{
    Pen clearColor = {200, 200, 200};

    Game::Button MenuButton(blit::Button::MENU); // "2" on keyboard
    // Button::X = "C" key

    uint32_t pTime = 0;

    extern SceneManager sceneMan;

    // Forward declares
    void draw_stats(uint32_t ms_start, uint32_t ms_end);
} // namespace Game

// -----------------------------------------------------------------
// Intialize
// -----------------------------------------------------------------
void init()
{
    drand48(); // Nudge the RNG

    set_screen_mode(ScreenMode::hires);

    std::cout << "Dimesions: " << screen.bounds.w << " x " << screen.bounds.h << std::endl;

    using namespace Game;

    sceneMan.init();

    // Add scenes that the manager will manage.
    sceneMan.add(std::make_unique<BootScene>("BootScene"));
    sceneMan.add(std::make_unique<SplashScene>("SplashScene"));
    sceneMan.add(std::make_unique<GameScene>("GameScene"));
    sceneMan.add(std::make_unique<ExitScene>("ExitScene"));
    sceneMan.add(std::make_unique<MenuScene>("MenuScene"));

    // std::cout << sceneMan.toString() << std::endl;

    // Select the scenes in the opposite order they will run.
    sceneMan.queue("SplashScene");
    sceneMan.queue("BootScene"); // Boot runs first so it is pushed last.

    // std::cout << sceneMan.toString() << std::endl;
}

// -----------------------------------------------------------------
// Update state
// -----------------------------------------------------------------
void update(uint32_t time)
{
    using namespace Game;

    uint32_t dt = time - pTime;

    // std::cout << "update: " << time << ", dt: " << dt << std::endl;

    bool moreScenes = sceneMan.update(dt);

    if (!moreScenes)
    {
        std::cout << "Goodbye World" << std::endl;
        exit(0);
    }

    MenuButton.update();

    if (MenuButton.pressed())
    {
        std::cout << "Goodbye World" << std::endl;
#ifdef TARGET_32BLIT_HW
        blit::api.exit(false);
#else
        exit(0);
#endif
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

    sceneMan.render();

    uint32_t ms_end = now();

    // ******************************************************
    // Debug visuals. Remove in release mode.
    // screen.pen = Pen(255, 127, 100);
    // screen.line(Vec2(0, Spout_ScrollLine), Vec2(screen.bounds.w, Spout_ScrollLine));

    Game::draw_stats(ms_start, ms_end);
    // ******************************************************
}
