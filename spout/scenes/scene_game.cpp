#include <iostream>

#include "scene_game.hpp"
#include "../scenes/scene_manager.hpp"
#include "../islands/island.hpp"
#include "../particles/activator_arc.hpp"
#include "../particles/particle_square.hpp"

namespace Game
{
    extern float randF();

    using namespace blit;

    GameScene::GameScene(std::string name) : Scene{name}
    {
        // We don't want this scene to be thrown out when moving to another scene,
        // instead re-pool it.
        disposeOnExit = false;

        activator = std::make_unique<ActivatorArc>();
        activator->setMaxLifetime(10);

        // Set up explosion particles
        for (size_t i = 0; i < MaxExplosionParticles; i++)
        {
            auto p = std::make_unique<ParticleSquare>(i);
            p->setColor(Pen(255, 255, 255));
            ps.addParticle(std::move(p));
        }
    }

    void GameScene::update(uint32_t time)
    {
        switch (gameState)
        {
        case State::Play:
            update_play(time);
            break;
        case State::ExitPlay:
            update_dieing(time);
            break;
        case State::PlayAgain:
            update_dialogPlayAgain(time);
            break;

        default:
            break;
        }
    }

    void GameScene::render()
    {
        switch (gameState)
        {
        case State::Play:
            render_play();
            break;
        case State::ExitPlay:
            render_dieing();
            break;
        case State::Reset:
            render_dieing();
            ship.reset();
            playTime = 0;
            score = 0;
            altitude = 0;
            gameState = State::Play;
            break;
        case State::PlayAgain:
            render_dialogPlayAgain();
            DPAD_LEFTButton.reset();
            DPAD_RIGHTButton.reset();
            AButton.reset();
            break;

        default:
            break;
        }
    }

    std::string GameScene::nextScene()
    {
        if (menuRequested)
            return "MenuScene";
        else
            return "";
    }

    void GameScene::enterScene()
    {
        menuRequested = false;
        gameState = State::Play;
        explodeCnt = 0;
        markerP = markerPlayAgain;

        ship.init();

        buffer.clear();

        islands.init(3);

        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void GameScene::exitScene()
    {
    }

    void GameScene::update_play(uint32_t time)
    {
        menuButton.update();
        if (menuButton.tapped())
        {
            menuRequested = true;
            // Show menu
            state = SceneState::Exit; // Signal scene is done and wants to exit
        }

        // -----------------------------------------
        // Rotate
        DPAD_LEFTButton.update();
        DPAD_RIGHTButton.update();
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
        AButton.update();
        ship.applyThrust(AButton.pressed());

        // -----------------------------------------
        // Debug time suspending
        YButton.update();
        if (YButton.tapped())
        {
            updateEnabled = !updateEnabled;
        }

        if (updateEnabled)
            ship.update(time, gravity);
        bool hitFloor = ship.isDead();

        // -----------------------------------------
        // Scrolling
        if (ship.hitTripWire())
        {
            islands.update(time, buffer);
            altitude++;
        }

        // -----------------------------------------
        // Collision
        buffer.collide(ship);

        if (ship.isDead() || hitFloor)
        {
            if (hitFloor)
            {
                // Focus all the particles upwards
                activator->setStartAngle(DegreeToRadians * -90);
                activator->setEndAngle(DegreeToRadians * 90);
            }
            else
            {
                activator->setStartAngle(DegreeToRadians * 0);
                activator->setEndAngle(DegreeToRadians * 359);
            }

            // ship.reset();
            gameState = State::ExitPlay;
            // When we switch states the button could still be pressed which would
            // trigger the resultant menu inadvertantly. So we artifically release it.
            AButton.reset();

            ps.setPosition(ship.posX(), ship.posY() - 1);
            ps.triggerExplosion(activator);
        }

        playTime += float(time) / 1000.0;
        score = ship.Score();
    }

    void GameScene::render_dieing()
    {
        buffer.blit();

        ps.render();

        render_info();
    }

    void GameScene::render_play()
    {
        buffer.blit();

        ship.render();

        render_info();
    }

    void GameScene::render_info()
    {
        screen.pen = Pen(64, 64, 64, 127);
        screen.rectangle(Rect(0, 0, screen.bounds.w, 14));

        screen.pen = Pen(255, 255, 255);
        sprintf(infoLineBuffer, "%06d", altitude);
        screen.text("Alt: " + std::string(infoLineBuffer), minimal_font, Point(5, 4));

        sprintf(infoLineBuffer, "%05d", int(playTime));
        screen.text("Time: " + std::string(infoLineBuffer), minimal_font, Point(screen.bounds.w - 200, 4));

        sprintf(infoLineBuffer, "%07d", score);
        screen.text("Score: " + std::string(infoLineBuffer), minimal_font, Point(screen.bounds.w - 75, 4));
    }

    void GameScene::update_dieing(uint32_t time)
    {
        ps.update(time);

        // Update counter for explosion.
        if (explodeCnt > explodeDuration)
        {
            // Switch to displaying "Try again" dialog
            gameState = State::PlayAgain;
            explodeCnt = 0;
        }

        explodeCnt += time;
    }

    void GameScene::update_dialogPlayAgain(uint32_t time)
    {
        ps.update(time);

        DPAD_UpButton.update();
        DPAD_DownButton.update();
        AButton.update();

        if (DPAD_UpButton.tapped())
        {
            if (markerP != markerPlayAgain)
                markerP = markerPlayAgain;
        }
        else if (DPAD_DownButton.tapped())
        {
            if (markerP != markerNoWay)
                markerP = markerNoWay;
        }
        else if (AButton.tapped())
        {
            if (markerP == markerPlayAgain)
            {
                gameState = State::Reset;

                // gameState = State::Play;
            }
            else
            {
                // Go back to the main menu
                menuRequested = true;
                state = SceneState::Exit; // Signal scene is done and wants to exit
            }
        }
    }

    void GameScene::render_dialogPlayAgain()
    {
        buffer.blit();

        ps.render();

        // Center dialog
        int32_t dw = 100;
        int32_t dh = 50;
        int32_t xo = 20;
        int32_t wc = screen.bounds.w / 2;
        int32_t hc = screen.bounds.h / 2;

        int32_t dx = wc - dw / 2;
        int32_t dy = hc - dh / 2;

        screen.pen = Pen(127, 127, 127, 127);
        screen.rectangle(Rect(dx, dy, dw, dh));
        screen.pen = Pen(255, 255, 255);
        screen.line(Point(dx, dy), Point(dx + dw, dy));
        screen.line(Point(dx + dw, dy), Point(dx + dw, dy + dh));
        screen.line(Point(dx + dw, dy + dh), Point(dx, dy + dh));
        screen.line(Point(dx, dy + dh), Point(dx, dy));

        screen.pen = Pen(0, 0, 0);
        screen.text("Menu:", minimal_font, Point(dx + xo, dy + 10));
        screen.text("    Play again", minimal_font, Point(dx + xo, dy + 22));
        screen.text("    Yeah...No!", minimal_font, Point(dx + xo, dy + 32));
        screen.pen = Pen(255, 255, 255);
        screen.text(" ->", minimal_font, Point(dx + xo, dy + markerP));

        render_info();
    }

} // namespace Game
