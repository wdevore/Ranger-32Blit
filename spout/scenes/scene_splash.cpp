#include <iostream>

#include "32blit.hpp"
#include "engine/api_private.hpp"

#include "../game/defines.hpp"
#include "scene_splash.hpp"

namespace Game
{
    extern GameSave gameSave;

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
        // return "GameScene";
        return "MenuScene";
    }

    void SplashScene::enterScene()
    {
        duration = 500; // 1 seconds
        durationCnt = 0;
        state = SceneState::OnStage; // Immediate transition onto the stage

        bool loaded = read_save(gameSave);
        if (loaded)
        {
            std::cout << "Loading scores from: '" << api.get_save_path() << "'" << std::endl;
            // std::cout << "Splash::enterScene Game scores loaded" << std::endl;
        }
        else
        {
            std::cout << "No Scores present on disc. Creating defaults." << std::endl;

            // Setup some defaults
            gameSave.scores[0] = {{'t', 'n', 'k'}, 100, 200, 10};
            gameSave.scores[1] = {{'w', 'r', 'c'}, 50, 100, 5};
            gameSave.scores[2] = {{'-', '-', '-'}, 0, 0, 0};
            gameSave.scores[3] = {{'-', '-', '-'}, 0, 0, 0};
            gameSave.scores[4] = {{'-', '-', '-'}, 0, 0, 0};

            write_save(gameSave);
        }
    }

    void SplashScene::exitScene()
    {
    }

} // namespace Game
