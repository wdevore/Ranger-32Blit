#include <iostream>

#include "32blit.hpp"
#include "scene_about.hpp"

namespace Game
{
    using namespace blit;

    AboutScene::AboutScene(std::string name) : Scene{name}
    {
        disposeOnExit = false;
    }

    void AboutScene::update(uint32_t time)
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

    void AboutScene::render()
    {
        screen.pen = Pen(64, 64, 64);
        int32_t vp = screen.bounds.h / 3;
        int32_t htp = screen.bounds.w / 5;
        int32_t th = 14;
        
        screen.rectangle(Rect(0, vp, screen.bounds.w, 14 * 4));

        screen.pen = Pen(255, 127, 0);
        screen.text("About:", minimal_font, Point(htp - 8, vp + 4));
        screen.text("   Ported to 32Blit by William Cleveland.", minimal_font, Point(htp, vp + 12+4));
        screen.text("   Jan 31 2021", minimal_font, Point(htp, vp + 22+4));
        screen.text("   Go as high and a fast as you can.", minimal_font, Point(htp, vp + 34+4));
        // screen.text("   Got it.", minimal_font, Point(htp, vp + 46+4));
    }

    std::string AboutScene::nextScene()
    {
        return "MenuScene";
    }

    void AboutScene::enterScene()
    {
        duration = 5000;
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage
    }

    void AboutScene::exitScene()
    {
    }

} // namespace Game
