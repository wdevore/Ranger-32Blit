#include <iostream>

#include "32blit.hpp"
#include "engine/api_private.hpp"

#include "../game/defines.hpp"
#include "scene_splash.hpp"
#include "../game/score_board.hpp"

namespace Game
{
    extern ScoreBoard scoreBoard;

    using namespace blit;

    SplashScene::SplashScene(std::string name) : Scene{name}
    {
        disposeOnExit = true;
    }

    void SplashScene::update(uint32_t time)
    {
        switch (state)
        {
        case SceneState::OnStage:
        {
            if (durationCnt > duration)
            {
                durationCnt = 0;
                state = SceneState::Exit; // Signal scene is done and wants to exit
            }

            durationCnt += time;
        }
        break;

        default:
            break;
        }
    }

    void SplashScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        screen.rectangle(Rect(0, screen.bounds.h / 2, screen.bounds.w, 14));
        screen.pen = Pen(0, 0, 0);
        screen.text("Splash", minimal_font, Point(5, screen.bounds.h / 2 + 4));
    }

    std::string SplashScene::nextScene()
    {
        return "MenuScene";
        // -- DEBUG
        // return "GameScene";
    }

    void SplashScene::enterScene()
    {
        duration = 500; // 1 seconds
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage

        scoreBoard.load();

        // char initials[] = {'x', 'x', 'x'};
        // int rank = scoreBoard.rankPlayer(10);
        // std::cout << "rank: " << rank << std::endl;
        // scoreBoard.setScore(rank, initials, 10, 110, 220);
        // std::cout << scoreBoard.toString();
    }

    void SplashScene::exitScene()
    {
    }

} // namespace Game
