#include <iostream>

#include "32blit.hpp"
#include "scene_boot.hpp"

namespace Game
{
    using namespace blit;

    BootScene::BootScene(std::string name) : Scene{name}
    {
    }

    void BootScene::init()
    {
        duration = 2000; // 2 seconds
        duractionCnt = 0;
    }

    bool BootScene::update(uint32_t time)
    {
        // std::cout << "BootScene::update :" << time << std::endl;
        if (duractionCnt > duration)
        {
            // std::cout << "BootScene::update finished: " << duractionCnt << std::endl;
            duractionCnt = 0;
            return true; // Signal scene is done
        }

        duractionCnt += time;
        // std::cout << "BootScene::update " << duractionCnt << std::endl;

        return false;
    }

    void BootScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        screen.rectangle(Rect(0, 0, screen.bounds.w, 14));
        screen.pen = Pen(0, 0, 0);
        screen.text("Booting", minimal_font, Point(5, 4));
    }

} // namespace Game
