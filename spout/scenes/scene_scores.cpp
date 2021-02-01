#include <iostream>

#include "32blit.hpp"
#include "scene_scores.hpp"
#include "../game/defines.hpp"
#include "../game/score_board.hpp"

namespace Game
{
    extern ScoreBoard scoreBoard;

    using namespace blit;

    ScoresScene::ScoresScene(std::string name) : Scene{name}
    {
        disposeOnExit = false;
    }

    void ScoresScene::update(uint32_t time)
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

    void ScoresScene::render()
    {
        screen.pen = Pen(64, 64, 64);
        int32_t vp = screen.bounds.h / 3;
        int32_t htp = screen.bounds.w / 5;
        int32_t th = 14;

        screen.rectangle(Rect(0, vp, screen.bounds.w, 20 * 4));

        screen.pen = Pen(255, 127, 64);

        screen.text("Scores:", minimal_font, Point(htp - 8, vp + 4));

        GameScore gs = scoreBoard.score(0);
        sprintf(lineBuf, "    %c%c%c: Altitude (%d) Score (%d) Time (%d)",
                gs.initials[0], gs.initials[1], gs.initials[2],
                gs.altitude, gs.score, gs.time);
        screen.text(std::string(lineBuf), minimal_font, Point(htp, vp + 12 + 4));

        gs = scoreBoard.score(1);
        sprintf(lineBuf, "    %c%c%c: Altitude (%d) Score (%d) Time (%d)",
                gs.initials[0], gs.initials[1], gs.initials[2],
                gs.altitude, gs.score, gs.time);
        screen.text(std::string(lineBuf), minimal_font, Point(htp, vp + 22 + 4));

        gs = scoreBoard.score(2);
        sprintf(lineBuf, "    %c%c%c: Altitude (%d) Score (%d) Time (%d)",
                gs.initials[0], gs.initials[1], gs.initials[2],
                gs.altitude, gs.score, gs.time);
        screen.text(std::string(lineBuf), minimal_font, Point(htp, vp + 32 + 4));

        gs = scoreBoard.score(3);
        sprintf(lineBuf, "    %c%c%c: Altitude (%d) Score (%d) Time (%d)",
                gs.initials[0], gs.initials[1], gs.initials[2],
                gs.altitude, gs.score, gs.time);
        screen.text(std::string(lineBuf), minimal_font, Point(htp, vp + 42 + 4));

        gs = scoreBoard.score(4);
        sprintf(lineBuf, "    %c%c%c: Altitude (%d) Score (%d) Time (%d)",
                gs.initials[0], gs.initials[1], gs.initials[2],
                gs.altitude, gs.score, gs.time);
        screen.text(std::string(lineBuf), minimal_font, Point(htp, vp + 52 + 4));
    }

    std::string ScoresScene::nextScene()
    {
        return "MenuScene";
    }

    void ScoresScene::enterScene()
    {
        duration = 5000;
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void ScoresScene::exitScene()
    {
    }

} // namespace Game
