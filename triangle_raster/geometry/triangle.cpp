#include "triangle.hpp"

namespace Geometry
{
    template <typename T>
    int signum(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    void flatTri::init(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        v1x = x1;
        v1y = y1;
        v2x = x1;
        v2y = y1;

        changed1 = false;
        changed2 = false;

        dx1 = abs(x2 - x1);
        dy1 = abs(y2 - y1);

        dx2 = abs(x3 - x1);
        dy2 = abs(y3 - y1);

        signx1 = signum(x2 - x1);
        signx2 = signum(x3 - x1);

        signy1 = signum(y2 - y1);
        signy2 = signum(y3 - y1);

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

        e1 = 2 * dy1 - dx1;
        e2 = 2 * dy2 - dx2;
    }

    // It's important that x2,y2 and x3,y3 lie on the same horizontal line, that is
    // y2 must be equal to y3. Thus be sure to split triangle into a top and bottom.
    void flatTri::render(blit::Surface &screen)
    {
        _v1x = v1x;
        _v1y = v1y;
        _v2x = v2x;
        _v2y = v2y;
        _e1 = e1;
        _e2 = e2;

        for (int i = 0; i <= dx1; i++)
        {
            p1.x = _v1x;
            p1.y = _v1y;
            p2.x = _v2x;
            p2.y = _v2y;

            screen.line(p1, p2);

            while (_e1 >= 0)
            {
                if (changed1)
                    _v1x += signx1;
                else
                    _v1y += signy1;
                _e1 = _e1 - 2 * dx1;
            }

            if (changed1)
                _v1y += signy1;
            else
                _v1x += signx1;

            _e1 = _e1 + 2 * dy1;

            // here we rendered the next point on line 1 so follow now line 2
            // until we are on the same y-value as line 1.
            while (_v2y != _v1y)
            {
                while (_e2 >= 0)
                {
                    if (changed2)
                        _v2x += signx2;
                    else
                        _v2y += signy2;
                    _e2 = _e2 - 2 * dx2;
                }

                if (changed2)
                    _v2y += signy2;
                else
                    _v2x += signx2;

                _e2 = _e2 + 2 * dy2;
            }
        }
    }

    Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        vertices[0] = {0, 0};
        vertices[1] = {0, 0};
        vertices[2] = {0, 0};

        set(x1, y1, x2, y2, x3, y3);
    }

    void Triangle::sort(int &x1, int &y1, int &x2, int &y2, int &x3, int &y3)
    {
        int x;
        int y;

        if (y1 > y2)
        {
            x = x1;
            y = y1;
            x1 = x2;
            y1 = y2;
            x2 = x;
            y2 = y;
        }

        // here y1 <= y2
        if (y1 > y3)
        {
            x = x1;
            y = y1;
            x1 = x3;
            y1 = y3;
            x3 = x;
            y3 = y;
        }

        // here y1 <= y2 and y1 <= y3 so test vertex 2 vs. vertex 3
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

    void Triangle::set(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        vertices[0].x = x1;
        vertices[0].y = y1;

        vertices[1].x = x2;
        vertices[1].y = y2;

        vertices[2].x = x3;
        vertices[2].y = y3;

        // sort the three vertices by y-coordinate ascending,
        // so x1,y1 is the topmost (max y) vertex
        sort(x1, y1, x2, y2, x3, y3);

        flatTop = false;
        flatBot = false;

        // check for trivial case of bottom-flat triangle
        if (y2 == y3)
        {
            fB.init(x1, y1, x2, y2, x3, y3);
            flatBot = true;
        }
        // check for trivial case of top-flat triangle
        else if (y1 == y2)
        {
            fT.init(x3, y3, x1, y1, x2, y2);
            flatTop = true;
        }
        else
        {
            // general case - split the triangle in a topflat and bottom-flat one
            int x = (int)(x1 + (float(y2 - y1) / float(y3 - y1)) * (x3 - x1));

            fB.init(x1, y1, x2, y2, x, y2);
            fT.init(x3, y3, x2, y2, x, y2);
            flatBot = true;
            flatTop = true;
        }
    }

    // It's important that x2,y2 and x3,y3 lie on the same horizontal line, that is
    // y2 must be equal to y3. Thus be sure to split triangle prior.
    void Triangle::render(blit::Surface &screen)
    {
        if (flatTop)
            fT.render(screen);
        if (flatBot)
            fB.render(screen);
    }
} // namespace Geometry