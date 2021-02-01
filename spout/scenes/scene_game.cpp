#include <iostream>
#include <sstream>

#include "scene_game.hpp"
#include "../scenes/scene_manager.hpp"
#include "../islands/island.hpp"
#include "../particles/activator_arc.hpp"
#include "../particles/activator_radial.hpp"
#include "../particles/particle_square.hpp"
#include "../game/mine.hpp"
#include "../game/score_board.hpp"

namespace Game
{
    extern float randF();
    extern ScoreBoard scoreBoard;

    using namespace blit;

    GameScene::GameScene(std::string name) : Scene{name}
    {
        // We don't want this scene to be thrown out when moving to another scene,
        // instead re-pool it.
        disposeOnExit = false;

        thrustActivator = std::make_unique<ActivatorArc>();
        thrustActivator->setMaxLifetime(20);

        mineExplodeActivator = std::make_unique<ActivatorRadial>();
        mineExplodeActivator->setMaxLifetime(3);

        // Set up explosion particles
        for (size_t i = 0; i < MaxExplosionParticles; i++)
        {
            auto p = std::make_unique<ParticleSquare>(1);
            p->setColor(Pen(255, 255, 255));
            explodePS.addParticle(std::move(p));
        }

        for (size_t i = 0; i < MaxExplosionParticles; i++)
        {
            auto p = std::make_unique<ParticleSquare>(2);
            p->setColor(Pen(127, 64, 0));
            minePS.addParticle(std::move(p));
        }

        std::list<std::string> mineMap = {
            "  ooo",
            " ooooo",
            "ooooooo",
            " ooooo",
            "  ooo",
        };

        mines.addMine(std::make_unique<Mine>(mineMap));
    }

    void GameScene::update(uint32_t time)
    {
        switch (gameState)
        {
        case State::EnterPlay:
            update_enterplay(time);
            break;
        case State::Play:
            update_play(time);
            break;
        case State::ExitPlay:
            update_dieing(time);
            break;
        case State::Continue:
            update_dialogContinue(time);
            break;
        case State::PlayAgain:
            update_dialogPlayAgain(time);
            break;
        case State::Ranking:
            update_dialogInitials(time);
            break;

        default:
            break;
        }
    }

    void GameScene::render()
    {
        switch (gameState)
        {
        case State::EnterPlay:
            render_enterplay();
            break;
        case State::Play:
            render_play();
            break;
        case State::ExitPlay:
            render_dieing();
            break;
        case State::Continue:
            render_dialogContinue();
            DPAD_LeftButton.reset();
            DPAD_RightButton.reset();
            AButton.reset();
            break;
        case State::PlayAgain:
            render_dialogPlayAgain();
            AButton.reset();
            break;
        case State::Ranking:
            render_dialogInitials();
            AButton.reset();
            break;
        case State::Reset:
            render_dieing();
            ship.reset();
            playTime = 0;
            score = 0;
            altitude = 0;
            gameState = State::Play;
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
        gameState = State::EnterPlay;
        // gameState = State::Ranking;
        explodeCnt = 0;
        markerP = markerFirstChoice;
        lives = 3;

        ship.init();

        buffer.clear();

        islands.init(3);

        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void GameScene::exitScene()
    {
    }

    void GameScene::update_enterplay(uint32_t time)
    {
        buffer.scroll();
        buffer.clearLine(0);

        // First scroll until a Island has reached the screen
        // Then scroll until Spout_ScrollLine reached.
        islands.update(time, buffer);
        mines.update(time, buffer);

        buffer.scroll();
        buffer.clearLine(0);
        islands.update(time, buffer);
        mines.update(time, buffer);

        if (scrollCnt > scrollAmt)
        {
            gameState = State::Play;
            scrollCnt = 0;
        }
        scrollCnt++;
    }

    void GameScene::render_enterplay()
    {
        buffer.blit();

        render_info();
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
        DPAD_LeftButton.update();
        DPAD_RightButton.update();
        if (DPAD_LeftButton.pressed())
        {
            ship.rotateCCW();
        }
        else if (DPAD_RightButton.pressed())
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
            buffer.scroll();
            // Clear top line from previous scroll
            buffer.clearLine(0);

            islands.update(time, buffer);
            mines.update(time, buffer);
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
                thrustActivator->setStartAngle(DegreeToRadians * -90);
                thrustActivator->setEndAngle(DegreeToRadians * 90);
            }
            else
            {
                thrustActivator->setStartAngle(DegreeToRadians * 0);
                thrustActivator->setEndAngle(DegreeToRadians * 359);
            }

            lives--;
            if (lives == 0)
            {
                lives = 0;
                rank = scoreBoard.rankPlayer(altitude);
                if (rank == 0)
                {
                    // Switch to "Play Again" dialog
                    gameState = State::PlayAgain;
                }
                else
                {
                    // Switch to "Rank dialog"
                    gameState = State::Ranking;
                    initials[0] = ' ';
                    initials[1] = ' ';
                    initials[2] = ' ';
                }

                AButton.reset();
            }
            else
            {
                gameState = State::ExitPlay;
            }

            // When we switch states the button could still be pressed which would
            // trigger the resultant menu inadvertantly. So we artifically release it.
            AButton.reset();

            explodePS.setPosition(ship.posX(), ship.posY() - 1);
            explodePS.triggerExplosion(thrustActivator);
        }

        minePS.update(time);
        buffer.collide(minePS);

        if (ship.hasHitMine() && !minePS.isActive())
        {
            // explode mine and increment score
            ship.addToScore(100);
            minePS.setPosition(ship.posX(), ship.posY() - 1);
            minePS.triggerExplosion(mineExplodeActivator);
        }

        playTime += float(time) / 1000.0;
        score = ship.Score();
    }

    void GameScene::render_play()
    {
        buffer.blit();

        minePS.render();

        ship.render();

        render_info();
    }

    void GameScene::update_dieing(uint32_t time)
    {
        explodePS.update(time);

        // Update counter for explosion.
        if (explodeCnt > explodeDuration)
        {
            // Switch to displaying "Try again" dialog
            gameState = State::Continue;
            explodeCnt = 0;
        }

        buffer.collide(explodePS);

        explodeCnt += time;
    }

    void GameScene::render_dieing()
    {
        buffer.blit();

        explodePS.render();

        render_info();
    }

    void GameScene::update_dialogContinue(uint32_t time)
    {
        explodePS.update(time);

        DPAD_UpButton.update();
        DPAD_DownButton.update();
        AButton.update();

        if (DPAD_UpButton.tapped())
        {
            if (markerP != markerFirstChoice)
                markerP = markerFirstChoice;
        }
        else if (DPAD_DownButton.tapped())
        {
            if (markerP != markerSecondChoice)
                markerP = markerSecondChoice;
        }
        else if (AButton.tapped())
        {
            if (markerP == markerFirstChoice)
            {
                gameState = State::Play;
                ship.reset();
            }
            else
            {
                // Go back to the main menu
                menuRequested = true;
                state = SceneState::Exit; // Signal scene is done and wants to exit
            }
        }

        buffer.collide(explodePS);
    }

    void GameScene::render_dialogContinue()
    {
        buffer.blit();

        explodePS.render();

        // Center dialog
        int32_t dw = 100;
        int32_t dh = 50;
        int32_t xo = 20;
        int32_t wc = screen.bounds.w / 2;
        int32_t hc = screen.bounds.h / 2;

        int32_t dx = wc - dw / 2;
        int32_t dy = hc - dh / 2;

        screen.pen = Pen(127, 127, 127, 200);
        screen.rectangle(Rect(dx, dy, dw, dh));
        screen.pen = Pen(255, 255, 255);
        screen.line(Point(dx, dy), Point(dx + dw, dy));
        screen.line(Point(dx + dw, dy), Point(dx + dw, dy + dh));
        screen.line(Point(dx + dw, dy + dh), Point(dx, dy + dh));
        screen.line(Point(dx, dy + dh), Point(dx, dy));

        screen.pen = Pen(0, 0, 0);
        screen.text("Menu:", minimal_font, Point(dx + xo, dy + 10));
        screen.text("    Continue?", minimal_font, Point(dx + xo, dy + 22));
        screen.text("    Yeah...No!", minimal_font, Point(dx + xo, dy + 32));
        screen.pen = Pen(255, 255, 255);
        screen.text(" ->", minimal_font, Point(dx + xo, dy + markerP));

        render_info();
    }

    void GameScene::update_dialogInitials(uint32_t time)
    {
        explodePS.update(time);

        // Left/Right changes character position
        // Up/Down changes character

        DPAD_UpButton.update();
        DPAD_DownButton.update();
        DPAD_LeftButton.update();
        DPAD_RightButton.update();
        AButton.update();

        if (DPAD_UpButton.tapped())
        {
            // scroll backwards through the alphabet
            initialChar[initialIdx]--;
            if (initialChar[initialIdx] < 0)
                initialChar[initialIdx] = 26;
            initials[initialIdx] = alpha[initialChar[initialIdx]];
        }
        else if (DPAD_DownButton.tapped())
        {
            // scroll forwards through the alphabet
            initialChar[initialIdx] = (initialChar[initialIdx] + 1) % 27;
            initials[initialIdx] = alpha[initialChar[initialIdx]];
        }
        else if (AButton.tapped())
        {
            scoreBoard.setScore(rank, initials, altitude, ship.Score(), playTime);
            scoreBoard.save();
            gameState = State::PlayAgain;
        }
        else if (DPAD_LeftButton.tapped())
        {
            initialPos -= 5;
            if (initialPos < 0)
                initialPos = 10;
            initialIdx -= 1;
            if (initialIdx < 0)
                initialIdx = 2;
        }
        else if (DPAD_RightButton.tapped())
        {
            initialPos += 5;
            if (initialPos > 10)
                initialPos = 0;
            initialIdx = (initialIdx + 1) % 3;
        }

        if (blinkCnt > blinkRate)
        {
            cursorVisble = !cursorVisble;
            blinkCnt = 0;
        }
        blinkCnt += time;
    }

    void GameScene::render_dialogInitials()
    {
        buffer.blit();

        explodePS.render();

        // Center dialog
        int32_t dw = 200;
        int32_t dh = 75;
        int32_t xo = 20;
        int32_t wc = screen.bounds.w / 2;
        int32_t hc = screen.bounds.h / 2;

        int32_t dx = wc - dw / 2;
        int32_t dy = hc - dh / 2;

        screen.pen = Pen(127, 127, 127, 200);
        screen.rectangle(Rect(dx, dy, dw, dh));

        screen.pen = Pen(255, 255, 255);
        screen.text("Enter 3 Letters", minimal_font, Point(dx + xo - 5, dy + 10));

        screen.pen = Pen(0, 0, 0);
        std::stringstream ss;
        ss << initials[0] << initials[1] << initials[2];
        xo += 50;
        int yo = 10;
        screen.text(ss.str(), minimal_font, Point(dx + xo, dy + yo + 17));

        if (cursorVisble)
        {
            screen.pen = Pen(255, 127, 127);
            screen.line(Point(dx + xo + initialPos, dy + yo + 24), Point(dx + xo + initialPos + 3, dy + yo + 24));
            screen.line(Point(dx + xo + initialPos, dy + yo + 25), Point(dx + xo + initialPos + 3, dy + yo + 25));
        }

        xo -= 45;
        screen.pen = Pen(255, 255, 255);
        screen.text("Up/Down changes letter", minimal_font, Point(dx + xo - 10, dy + 42));
        screen.text("Left/Right changes position", minimal_font, Point(dx + xo - 10, dy + 50));
        screen.text("A button means done", minimal_font, Point(dx + xo - 10, dy + 58));

        render_info();
    }

    void GameScene::update_dialogPlayAgain(uint32_t time)
    {
        explodePS.update(time);

        DPAD_UpButton.update();
        DPAD_DownButton.update();
        AButton.update();

        if (DPAD_UpButton.tapped())
        {
            if (markerP != markerFirstChoice)
                markerP = markerFirstChoice;
        }
        else if (DPAD_DownButton.tapped())
        {
            if (markerP != markerSecondChoice)
                markerP = markerSecondChoice;
        }
        else if (AButton.tapped())
        {
            if (markerP == markerFirstChoice)
            {
                gameState = State::EnterPlay;
                buffer.clear();
                ship.reset();
                playTime = 0;
                ship.clearScore();
                altitude = 0;
                lives = 3;
            }
            else
            {
                // Go back to the main menu
                menuRequested = true;
                state = SceneState::Exit; // Signal scene is done and wants to exit
            }
        }

        buffer.collide(explodePS);
    }

    void GameScene::render_dialogPlayAgain()
    {
        buffer.blit();

        explodePS.render();

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
        screen.text("    PlayAgain", minimal_font, Point(dx + xo, dy + 22));
        screen.text("    Yeah...No!", minimal_font, Point(dx + xo, dy + 32));
        screen.pen = Pen(255, 255, 255);
        screen.text(" ->", minimal_font, Point(dx + xo, dy + markerP));

        render_info();
    }

    void GameScene::render_info()
    {
        screen.pen = Pen(64, 64, 64, 127);
        screen.rectangle(Rect(0, 0, screen.bounds.w, 14));

        screen.pen = Pen(255, 255, 255);
        sprintf(infoLineBuffer, "%06d", altitude);
        screen.text("Alt: " + std::string(infoLineBuffer), minimal_font, Point(5, 4));

        sprintf(infoLineBuffer, "%02d", lives);
        screen.text("Lives: " + std::string(infoLineBuffer), minimal_font, Point(screen.bounds.w - 225, 4));

        sprintf(infoLineBuffer, "%05d", int(playTime));
        screen.text("Time: " + std::string(infoLineBuffer), minimal_font, Point(screen.bounds.w - 150, 4));

        sprintf(infoLineBuffer, "%07d", score);
        screen.text("Score: " + std::string(infoLineBuffer), minimal_font, Point(screen.bounds.w - 75, 4));
    }

} // namespace Game
