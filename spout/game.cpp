#include <list>

#include "32blit.hpp"

#include "utilities.hpp"
#include "game.hpp"
#include "ship.hpp"
#include "island.hpp"
#include "island_buffer.hpp"

namespace Game
{
    Ship ship;
    Vec2 gravity = Vec2{0.0, GravityAcceleration};

    Pen clearColor = {200, 200, 200};

    std::list<std::unique_ptr<IsLand>> islands;

    State gameState = {State::Boot};

    std::list<std::string> islandMap = {
        "000011000000000",
        "001111100000000",
        "111111110000000",
        "011111111110000",
        "011111111110000",
        "001111111110000",
        "001111111111110",
        "011111111111111",
        "011111111111111",
        "001111111111111",
        "000111111111111",
        "000011111111110",
        "000111111111000",
        "000011111110000",
    };

    IslandBuffer buffer;

} // namespace Game
