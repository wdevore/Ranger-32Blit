#include <iostream>

#include "32blit.hpp"
#include "scene_game.hpp"
#include "../gui/button.hpp"
#include "../islands/island_buffer.hpp"
#include "../islands/island.hpp"
#include "../scenes/scene_manager.hpp"

namespace Game
{
    extern Ship ship; // Defined in game.cpp
    extern Vec2 gravity;
    extern Pen clearColor;

    Game::Button HomeButton(blit::Button::HOME);             // "1" on keyboard
    Game::Button AButton(blit::Button::A);                   // "Z" on keyboard
    Game::Button YButton(blit::Button::Y);                   // "V" on keyboard
    Game::Button DPAD_LEFTButton(blit::Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
    Game::Button DPAD_RIGHTButton(blit::Button::DPAD_RIGHT); // "->" or "D" on keyboard.
    // Button::X = "C" key

    // uint32_t pTime = 0;
    bool updateEnabled = true;

    // extern std::list<std::unique_ptr<IsLand>> islands;
    extern std::list<std::string> islandMap;

    extern State gameState;
    extern IslandBuffer buffer;

    extern SceneManager sceneMan;

    using namespace blit;

    GameScene::GameScene(std::string name) : Scene{name}
    {
        // We don't want this scene to be thrown out, instead re-pool it.
        disposeOnExit = false;
    }

    void GameScene::update(uint32_t time)
    {
        HomeButton.update();
        AButton.update();
        YButton.update();
        DPAD_LEFTButton.update();
        DPAD_RIGHTButton.update();

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
            ship.update(time, gravity);

        if (ship.hitTripWire())
            buffer.scroll();

        bool collided = buffer.collide(ship);

        if (ship.isDead())
        {
            ship.reset();
        }
    }

    void GameScene::render()
    {
        buffer.blit();

        ship.render();

        screen.pen = Pen(255, 255, 255, 127);
        screen.rectangle(Rect(0, 0, screen.bounds.w, 14));
        screen.pen = Pen(0, 0, 0);
        screen.text("Alt: 0123  ---  Score: 130", minimal_font, Point(5, 4));
    }

    std::string GameScene::NextScene()
    {
        return ""; //"MenuScene";
    }

    void GameScene::EnterScene()
    {
        ship.init();

        buffer.clear();

        int xoff = 100;
        int yoff = 100;
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
        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void GameScene::ExitScene()
    {
    }

} // namespace Game
