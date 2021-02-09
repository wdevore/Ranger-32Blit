#include "32blit.hpp"

#include "../game/defines.hpp"
#include "scene.hpp"
#include "../gui/button.hpp"
#include "../geometry/triangle.hpp"

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

        char infoLineBuffer[100];
        State gameState;

        Point p1;
        Point p2;
        Pen lineColor1 = {255, 127, 0};
        Pen lineColor2 = {64, 64, 64};
        Pen lineColor3 = {128, 128, 128};
        float ay = 0.0;
        float aydir = 1.0;
        float bx = 0.0;
        float bxdir = 1.0;
        float c = 0.0;
        float cdir = 1.0;

        Geometry::Triangle greenTri = {50, 50, 100, 100, 75, 0};

        void fillFlatSideTriangleInt(float x1, float y1, float x2, float y2, float x3, float y3);

        void fillBottomFlatTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
        void fillTopFlatTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
        void sortVerticesAscendingByY(float &x1, float &y1, float &x2, float &y2, float &x3, float &y3);

    public:
        GameScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;

        void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
        void drawTriangleInt(float x1, float y1, float x2, float y2, float x3, float y3);

        void drawTriangle();
    };

} // namespace Game