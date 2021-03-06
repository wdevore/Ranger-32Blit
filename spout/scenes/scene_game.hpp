#include "32blit.hpp"

#include "../game/defines.hpp"
#include "scene.hpp"
#include "../gui/button.hpp"
#include "../islands/island_buffer.hpp"
#include "../islands/islands.hpp"
#include "../islands/mines.hpp"
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
        Game::Button DPAD_LeftButton = Game::Button(blit::Button::DPAD_LEFT);   // "<-" or "A" on keyboard.
        Game::Button DPAD_RightButton = Game::Button(blit::Button::DPAD_RIGHT); // "->" or "D" on keyboard.
        Game::Button DPAD_UpButton = Game::Button(blit::Button::DPAD_UP);       // "W" on keyboard.
        Game::Button DPAD_DownButton = Game::Button(blit::Button::DPAD_DOWN);   // "S" on keyboard.

        // Button::X = "C" key

        State gameState;
        Ship ship; // Defined in game.cpp
        Vec2 gravity = Vec2{0.0, GravityAcceleration};

        IsLands islands;
        Mines mines;
        IslandBuffer buffer;

        uint32_t explodeDuration = 2000; // 2 seconds before dialog shows
        uint32_t explodeCnt = 0;

        // The particle system used to display ship exploding
        ParticleSystem explodePS{1};
        ParticleSystem minePS{2};
        std::unique_ptr<ParticleActivator> thrustActivator;
        std::unique_ptr<ParticleActivator> mineExplodeActivator;

        bool updateEnabled = true;
        int32_t markerFirstChoice = 22;
        int32_t markerSecondChoice = 32;
        int32_t markerP = markerFirstChoice;

        int altitude = 0;
        int score = 0;
        float playTime = 0.0;
        int lives = 3;
        int rank = 0;
        
        char alpha[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
        // int initialChar = 0;
        int initialChar[3] = {0, 0, 0};
        int initialIdx = 0;
        bool cursorVisble = true;
        int blinkCnt = 0;
        int blinkRate = 250;

        char initials[3] = {' ', ' ', ' '};
        int initialPos = 0;

        int scrollCnt = 0;
        int scrollAmt = 75;

        // Every waypoint a bonus is given = Amt - "Seconds passed".
        int waypointAmt = 100;
        int waypointCnt = 0;

        char infoLineBuffer[100];

        void update_enterplay(uint32_t time);
        void render_enterplay();

        void update_play(uint32_t time);
        void render_play();

        void update_dieing(uint32_t time);
        void render_dieing();

        void update_dialogContinue(uint32_t time);
        void render_dialogContinue();

        void update_dialogInitials(uint32_t time);
        void render_dialogInitials();

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