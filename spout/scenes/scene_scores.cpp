#include <iostream>

#include "32blit.hpp"
#include "scene_scores.hpp"

namespace Game
{
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
        
        screen.rectangle(Rect(0, vp, screen.bounds.w, 14 * 4));

        screen.pen = Pen(255, 127, 0);
        screen.text("Scores:", minimal_font, Point(htp - 8, vp + 4));
        screen.text("   WRC: Points 123, Atltitude 99", minimal_font, Point(htp, vp + 12+4));
        screen.text("   WRC: Points 666, Atltitude 42", minimal_font, Point(htp, vp + 22+4));
        screen.text("   WRC: Points 333, Atltitude 101", minimal_font, Point(htp, vp + 34+4));
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
