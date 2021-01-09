#include "32blit.hpp"

using namespace blit;

#include "parameter.hpp"

namespace Game
{
    class IsLand
    {
    private:
        int id;
        Pen color = {64, 64, 64};
        // Bounding dimensions
        int width;
        int height;
        int hCnt;

        // Line Parameters:
        Parameter shiftRate = {1, 1, 0.2, 0.3}; // How fast the line shifts Left or Right

        int shiftDuration;  // How long the line is allowed to shift. -1 = No shift
        Parameter shiftGap; // How long between and changes
        int shiftRange;     // How far, in either direction, shifting can go. Reletive to center.

        int leftPointRate;     // How fast the end point shifts
        int leftPointDuration; // How long the point is allowed to shift.
        int leftGap;           // How long between and changes
        int leftRange;         // How far, in either direction = Min/Max

        int rightPointRate;     // How fast the end point shifts
        int rightPointDuration; // How long the point is allowed to shift.
        int rightGap;           // How long between and changes
        int rightRange;         // How far, in either direction

        bool _scroll = false;

    public:
        IsLand() = default;
        IsLand(int id);

        void scroll();
        void reset();

        void update(uint32_t time);
        void render();
    };

} // namespace Game