#include <list>

#include "32blit.hpp"

#include "ship.hpp"
#include "island.hpp"

namespace Game
{
    Ship ship;
    Vec2 gravity;

    Pen clearColor = {200, 200, 200};

    std::list<std::unique_ptr<IsLand>> islands;

} // namespace Game
