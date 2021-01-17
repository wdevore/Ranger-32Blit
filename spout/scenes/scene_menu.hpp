#include "32blit.hpp"

#include "scene.hpp"
#include "../gui/button.hpp"

namespace Game
{
    using namespace blit;

    class MenuScene : public Scene
    {
    private:
        int32_t markerP;
        int32_t markerMinP;
        int32_t markerMaxP;
        State menuState;
        const int32_t markerPlay = 4 * 3;
        const int32_t markerScores = 4 * 5;
        const int32_t markerAbout = 4 * 7;
        const int32_t markerQuit = 4 * 9;

        Game::Button DPAD_UpButton = Game::Button(blit::Button::DPAD_UP);     // "W" on keyboard.
        Game::Button DPAD_DownButton = Game::Button(blit::Button::DPAD_DOWN); // "S" on keyboard.
        Game::Button AButton = Game::Button(blit::Button::A);                 // "Z" on keyboard

    public:
        MenuScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;
    };

} // namespace Game