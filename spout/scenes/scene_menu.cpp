#include <iostream>

#include "scene_menu.hpp"
#include "../game/game.hpp"

namespace Game
{

    using namespace blit;

    MenuScene::MenuScene(std::string name) : Scene{name}
    {
        disposeOnExit = false;
    }

    void MenuScene::update(uint32_t time)
    {
        switch (state)
        {
        case SceneState::OnStage:
        {
            DPAD_UpButton.update();
            DPAD_DownButton.update();
            AButton.update();

            if (DPAD_UpButton.tapped())
            {
                markerP -= 4 * 2;
                if (markerP < markerMinP)
                    markerP = markerMinP;
            }
            else if (DPAD_DownButton.tapped())
            {
                markerP += 4 * 2;
                if (markerP > markerMaxP)
                    markerP = markerMaxP;
            }
            else if (AButton.tapped())
            {
                int32_t vp = screen.bounds.h / 3;
                if (markerP == vp + 4 * 3)
                {
                    state = SceneState::Exit; // Signal scene is done and wants to exit
                    menuState = State::Play;
                    std::cout << "MenuScene Play" << std::endl;
                }
                else if (markerP == vp + 4 * 5)
                {
                    state = SceneState::Exit; // Signal scene is done and wants to exit
                    menuState = State::Exit;
                    std::cout << "MenuScene Quit" << std::endl;
                }
            }
        }
        break;

        default:
            break;
        }
    }

    void MenuScene::render()
    {
        screen.pen = Pen(255, 255, 255);
        int32_t vp = screen.bounds.h / 3;
        int32_t htp = screen.bounds.w / 3;
        int32_t th = 14;

        screen.rectangle(Rect(0, vp, screen.bounds.w, 14 * 3));

        screen.pen = Pen(255, 127, 0);
        screen.text("Menu:", minimal_font, Point(htp, vp + 4));
        screen.text("   Play game", minimal_font, Point(htp, vp + 4 * 3));
        screen.text("   Quit", minimal_font, Point(htp, vp + 4 * 5));

        screen.pen = Pen(0, 0, 0);
        screen.text("->", minimal_font, Point(htp, markerP));
    }

    std::string MenuScene::nextScene()
    {
        // When Menu exits the stage it needs to "recommend" another scene to transition to.
        switch (menuState)
        {
        case State::Play:
            return "GameScene";
        case State::Exit:
            return "ExitScene";

        default:
            return "";
            break;
        }
    }

    void MenuScene::enterScene()
    {
        state = SceneState::OnStage; // Immediate transition onto the stage

        int32_t vp = screen.bounds.h / 3;
        markerP = vp + 4 * 3;
        markerMinP = markerP;
        markerMaxP = markerP + 4 * 2;
        menuState = {State::Menu};
    }

    void MenuScene::exitScene()
    {
    }

} // namespace Game
