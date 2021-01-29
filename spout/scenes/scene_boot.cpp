#include <iostream>

#include "32blit.hpp"
#include "scene_boot.hpp"

namespace Game
{
    using namespace blit;

    BootScene::BootScene(std::string name) : Scene{name}
    {
    }

    void BootScene::update(uint32_t time)
    {
        state = SceneState::Exit; // Signal scene is done and wants to exit
    }

    void BootScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        screen.rectangle(Rect(0, screen.bounds.h / 2, screen.bounds.w, 14));
        screen.pen = Pen(0, 0, 0);
        screen.text("Booting", minimal_font, Point(5, screen.bounds.h / 2 + 4));
    }

    void BootScene::enterScene()
    {
        duration = 100; // 0.5 seconds
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage

        rand();

        set_screen_mode(ScreenMode::hires);

        std::cout << "Dimesions: " << screen.bounds.w << " x " << screen.bounds.h << std::endl;
    }

    void BootScene::exitScene()
    {
    }

} // namespace Game
