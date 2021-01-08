#include "32blit.hpp"

using namespace blit;

class IsLand
{
private:
    int id;
    Pen color;
    // Bounding dimensions
    int width;
    int height;

    // Line Parameters:
    int ShiftRate;     // How fast the line shifts Left or Right
    int ShiftDuration; // How long the line is allowed to shift. -1 = No shift
    int ShiftGap;      // How long between and changes
    int ShiftRange;    // How far, in either direction, shifting can go. Reletive to center.

    int LeftPointRate;     // How fast the end point shifts
    int LeftPointDuration; // How long the point is allowed to shift.
    int LeftGap;           // How long between and changes
    int LeftRange;         // How far, in either direction = Min/Max

    int RightPointRate;     // How fast the end point shifts
    int RightPointDuration; // How long the point is allowed to shift.
    int RightGap;           // How long between and changes
    int RightRange;         // How far, in either direction

    bool _scroll;

public:
    IsLand() = default;
    IsLand(int id);

    void scroll();
    void update(uint32_t time);
    void render();
};
