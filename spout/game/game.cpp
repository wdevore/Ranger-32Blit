#include <list>

#include "32blit.hpp"

#include "defines.hpp"
#include "game.hpp"
#include "ship.hpp"
#include "../islands/island.hpp"
#include "../islands/island_buffer.hpp"

namespace Game
{
    Ship ship;
    Vec2 gravity = Vec2{0.0, GravityAcceleration};

    Pen clearColor = {200, 200, 200};

    std::list<std::unique_ptr<IsLand>> islands;

    State gameState = {State::Boot};

    IslandBuffer buffer;

} // namespace Game
