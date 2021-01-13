#include <iostream>

#include "32blit.hpp"
#include "scene_splash.hpp"

namespace Game
{
    using namespace blit;

    SplashScene::SplashScene(std::string name) : Scene{name}
    {
        disposeOnExit = false;
    }

    void SplashScene::init()
    {
        duration = 3000; // 3 seconds
        duractionCnt = 0;
    }

    bool SplashScene::update(uint32_t time)
    {
        if (duractionCnt > duration)
        {
            duractionCnt = 0;
            return true; // Signal scene is done
        }

        duractionCnt += time;

        return false;
    }

    void SplashScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        screen.rectangle(Rect(0, 0, screen.bounds.w, 14));
        screen.pen = Pen(0, 0, 0);
        screen.text("Splash", minimal_font, Point(5, 4));
    }

} // namespace Game
