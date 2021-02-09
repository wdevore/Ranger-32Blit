#include "32blit.hpp"

#include "vertex.hpp"

// This class is a single triangle rasterizer (i.e. no shared vertices)

namespace Geometry
{
    class flatTri
    {
    public:
        // ---------------------------------------------------------
        // These vars are changed/reset on each rendering pass.
        int _v1x;
        int _v1y;
        int _v2x;
        int _v2y;
        int _e1;
        int _e2;
        // ---------------------------------------------------------

        // These vars are only changed when a vertex changes.
        int v1x;
        int v1y;
        int v2x;
        int v2y;
        int e1;
        int e2;

        bool changed1;
        bool changed2;

        int dx1;
        int dy1;
        int dx2;
        int dy2;

        int signx1;
        int signx2;
        int signy1;
        int signy2;

        blit::Point p1;
        blit::Point p2;

        void init(int x1, int y1, int x2, int y2, int x3, int y3);
        void render(blit::Surface &screen);
    };

    class Triangle
    {
    private:
        flatTri fT;
        flatTri fB;

        bool flatTop = false;
        bool flatBot = false;

        void sort(int &x1, int &y1, int &x2, int &y2, int &x3, int &y3);

    public:
        Vertex vertices[3];

        Triangle() = default;
        Triangle(int x1, int y1, int x2, int y2, int x3, int y3);

        void set(int x1, int y1, int x2, int y2, int x3, int y3);

        void render(blit::Surface &screen);
    };
} // namespace Geometry