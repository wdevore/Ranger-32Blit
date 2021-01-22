#include "32blit.hpp"

#include "../game/defines.hpp"
#include "scene.hpp"
#include "../gui/button.hpp"
#include "../islands/island_buffer.hpp"
#include "../islands/islands.hpp"
#include "../game/ship.hpp"
#include "../particles/particle_system.hpp"

namespace Game
{
    using namespace blit;

    class GameScene : public Scene
    {
    private:
        bool menuRequested = false;
        Game::Button menuButton = Game::Button(blit::Button::HOME);             // "2" on keyboard
        Game::Button AButton = Game::Button(blit::Button::A);                   // "Z" on keyboard
        Game::Button YButton = Game::Button(blit::Button::Y);                   // "V" on keyboard
        Game::Button DPAD_LEFTButton = Game::Button(blit::Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
        Game::Button DPAD_RIGHTButton = Game::Button(blit::Button::DPAD_RIGHT); // "->" or "D" on keyboard.
        Game::Button DPAD_UpButton = Game::Button(blit::Button::DPAD_UP);       // "W" on keyboard.
        Game::Button DPAD_DownButton = Game::Button(blit::Button::DPAD_DOWN);   // "S" on keyboard.

        // Button::X = "C" key

        State gameState;
        Ship ship; // Defined in game.cpp
        Vec2 gravity = Vec2{0.0, GravityAcceleration};

        IsLands islands;
        IslandBuffer buffer;

        uint32_t explodeDuration = 200; // 2 seconds before dialog shows
        uint32_t explodeCnt = 0;

        // The system used to display ship exploding
        ParticleSystem ps;
        std::unique_ptr<ParticleActivator> activator;

        bool updateEnabled = true;
        int32_t markerPlayAgain = 22;
        int32_t markerNoWay = 32;
        int32_t markerP = markerPlayAgain;

        int32_t altitude = 0;
        int32_t score = 0;
        float playTime = 0.0;
        
        char infoLineBuffer[320];

        void update_play(uint32_t time);
        void render_play();

        void update_dieing(uint32_t time);
        void render_dieing();

        void update_dialogPlayAgain(uint32_t time);
        void render_dialogPlayAgain();

        void render_info();

    public:
        GameScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;
    };

} // namespace Game