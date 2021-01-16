#include <iostream>

#include "32blit.hpp"
#include "scene_exit.hpp"

namespace Game
{
    using namespace blit;

    ExitScene::ExitScene(std::string name) : Scene{name}
    {
        disposeOnExit = true;
    }

    void ExitScene::update(uint32_t time)
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

    void ExitScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        screen.rectangle(Rect(0, screen.bounds.h / 2, screen.bounds.w, 14));
        screen.pen = Pen(255, 127, 0);
        screen.text("Goodbye World!", minimal_font, Point(5, screen.bounds.h / 2 + 4));
    }

    std::string ExitScene::nextScene()
    {
        return "";
    }

    void ExitScene::enterScene()
    {
        duration = 2000;
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void ExitScene::exitScene()
    {
    }

} // namespace Game
