#include <iostream>
#include <sstream>

#include "scene_game.hpp"
#include "../scenes/scene_manager.hpp"

#define PRECISION 8

namespace Game
{
    extern float randF();

    using namespace blit;

    template <typename T>
    int signum(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    GameScene::GameScene(std::string name) : Scene{name}
    {
    }

    void GameScene::update(uint32_t time)
    {
        float s = 0.1;
        if (ay < -25)
            aydir = s;

        if (ay > 25)
            aydir = -s;

        ay += aydir;

        if (bx < -25)
            bxdir = s;

        if (bx > 25)
            bxdir = -s;

        if (c < -25)
            cdir = s;

        if (c > 25)
            cdir = -s;

        ay += aydir;
        bx += bxdir;
        c += cdir;
    }

    void GameScene::render()
    {
        float xc = screen.bounds.w / 2;
        float yc = screen.bounds.h / 2;

        // drawTriangleInt(0, yc, xc + 25, yc, 0, yc - 50);
        // drawTriangleInt(xc - 25, yc, xc + 25, yc, xc-25, yc - 50);
        // drawTriangleInt(xc - 25, yc, xc + 25, yc, xc-150, yc - 25);
        // drawTriangle(xc - 25, yc, xc + 25, yc, xc - 100, yc - 25);

        // screen.pen = lineColor3;
        // drawTriangleInt(0, screen.bounds.h - 1, screen.bounds.w - 1, screen.bounds.h - 1, 0, 0);

        // screen.pen = lineColor2;
        // drawTriangleInt(screen.bounds.w - 1, screen.bounds.h - 1, screen.bounds.w - 1, 0, 0, 0);

        screen.pen = lineColor1;
        drawTriangleInt(
            xc - c, yc + c,
            xc + 25, yc + ay,
            xc + bx, yc - 55);

        drawTriangle();
    }

    std::string GameScene::nextScene()
    {
        return "";
    }

    void GameScene::enterScene()
    {
        set_screen_mode(ScreenMode::hires);

        menuRequested = false;

        gameState = State::EnterPlay;

        state = SceneState::OnStage; // Immediate transition onto the stage

        ay = 0.0;
    }

    void GameScene::exitScene()
    {
    }

    // This method rasterizes a triangle using only integer variables by using a
    // modified bresenham algorithm.
    // It's important that v2 and v3 lie on the same horizontal line, that is
    // y2 must be equal to y3. There be sure to split triangle prior.
    void GameScene::fillFlatSideTriangleInt(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        int v1x = int(x1);
        int v1y = int(y1);
        int v2x = int(x1);
        int v2y = int(y1);

        bool changed1 = false;
        bool changed2 = false;

        int dx1 = int(abs(x2 - x1));
        int dy1 = int(abs(y2 - y1));

        int dx2 = int(abs(x3 - x1));
        int dy2 = int(abs(y3 - y1));

        int signx1 = int(signum(x2 - x1));
        int signx2 = int(signum(x3 - x1));

        int signy1 = int(signum(y2 - y1));
        int signy2 = int(signum(y3 - y1));

        if (dy1 > dx1)
        { // swap values
            int tmp = dx1;
            dx1 = dy1;
            dy1 = tmp;
            changed1 = true;
        }

        if (dy2 > dx2)
        { // swap values
            int tmp = dx2;
            dx2 = dy2;
            dy2 = tmp;
            changed2 = true;
        }

        int e1 = 2 * dy1 - dx1;
        int e2 = 2 * dy2 - dx2;

        for (int i = 0; i <= dx1; i++)
        {
            p1.x = v1x;
            p1.y = v1y;
            p2.x = v2x;
            p2.y = v2y;
            screen.line(p1, p2);

            while (e1 >= 0)
            {
                if (changed1)
                    v1x += signx1;
                else
                    v1y += signy1;
                e1 = e1 - 2 * dx1;
            }

            if (changed1)
                v1y += signy1;
            else
                v1x += signx1;

            e1 = e1 + 2 * dy1;

            // here we rendered the next point on line 1 so follow now line 2
            // until we are on the same y-value as line 1.
            while (v2y != v1y)
            {
                while (e2 >= 0)
                {
                    if (changed2)
                        v2x += signx2;
                    else
                        v2y += signy2;
                    e2 = e2 - 2 * dx2;
                }

                if (changed2)
                    v2y += signy2;
                else
                    v2x += signx2;

                e2 = e2 + 2 * dy2;
            }
        }
    }

    void GameScene::fillBottomFlatTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        float invslope1 = (x2 - x1) / (y2 - y1);
        float invslope2 = (x3 - x1) / (y3 - y1);

        float xa = x1;
        float xb = x1 + 0.5;

        for (int scanlineY = y1; scanlineY <= y2; scanlineY++)
        {
            p1.x = (int)xa;
            p1.y = scanlineY;
            p2.x = (int)xb;
            p2.y = scanlineY;

            screen.line(p1, p2);

            xa += invslope1;
            xb += invslope2;
        }
    }

    void GameScene::fillTopFlatTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        float invslope1 = (x3 - x1) / (y3 - y1);
        float invslope2 = (x3 - x2) / (y3 - y2);

        float xa = x3;
        float xb = x3 + 0.5;

        for (int scanlineY = y3; scanlineY >= y1; scanlineY--)
        {
            p1.x = (int)xa;
            p1.y = scanlineY;
            p2.x = (int)xb;
            p2.y = scanlineY;

            screen.line(p1, p2);

            xa -= invslope1;
            xb -= invslope2;
        }
    }

    void GameScene::sortVerticesAscendingByY(float &x1, float &y1, float &x2, float &y2, float &x3, float &y3)
    {
        float x;
        float y;

        if (y1 > y2)
        {
            x = x1;
            y = y1;
            x1 = x2;
            y1 = y2;
            x2 = x;
            y2 = y;
        }

        // here v1.y <= v2.y
        if (y1 > y3)
        {
            x = x1;
            y = y1;
            x1 = x3;
            y1 = y3;
            x3 = x;
            y3 = y;
        }

        // here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3
        if (y2 > y3)
        {
            x = x2;
            y = y2;
            x2 = x3;
            y2 = y3;
            x3 = x;
            y3 = y;
        }
    }

    void GameScene::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        // at first sort the three vertices by y-coordinate ascending,
        // so p1 is the topmost vertice
        sortVerticesAscendingByY(x1, y1, x2, y2, x3, y3);

        // here we know that v1.y <= v2.y <= v3.y
        // check for trivial case of bottom-flat triangle
        if (y2 == y3)
        {
            fillBottomFlatTriangle(x1, y1, x2, y2, x3, y3);
        }
        // check for trivial case of top-flat triangle
        else if (y1 == y2)
        {
            fillTopFlatTriangle(x1, y1, x2, y2, x3, y3);
        }
        else
        {
            // general case - split the triangle in a topflat and bottom-flat one
            float x = (int)(x1 + ((y2 - y1) / (y3 - y1)) * (x3 - x1));
            float y = y2;

            fillBottomFlatTriangle(x1, y1, x2, y2, x, y);
            fillTopFlatTriangle(x2, y2, x, y, x3, y3);
        }
    }

    void GameScene::drawTriangleInt(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        x1 = int(x1);
        x2 = int(x2);
        x3 = int(x3);
        y1 = int(y1);
        y2 = int(y2);
        y3 = int(y3);
        
        // first sort the three vertices by y-coordinate ascending,
        // so x1,y1 is the topmost vertice
        sortVerticesAscendingByY(x1, y1, x2, y2, x3, y3);

        // here we know that y1 <= y2 <= y3

        // check for trivial case of bottom-flat triangle
        if (y2 == y3)
        {
            fillFlatSideTriangleInt(x1, y1, x2, y2, x3, y3);
        }
        // check for trivial case of top-flat triangle
        else if (y1 == y2)
        {
            fillFlatSideTriangleInt(x3, y3, x1, y1, x2, y2);
        }
        else
        {
            // general case - split the triangle in a topflat and bottom-flat one
            int x = (int)(x1 + (float(y2 - y1) / float(y3 - y1)) * (x3 - x1));

            fillFlatSideTriangleInt(x1, y1, x2, y2, x, y2);
            fillFlatSideTriangleInt(x3, y3, x2, y2, x, y2);
        }
    }

    void GameScene::drawTriangle()
    {
        screen.pen = {127, 255, 127};

        greenTri.render(screen);
    }

} // namespace Game
