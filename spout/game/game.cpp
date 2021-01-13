#include <list>

#include "32blit.hpp"

#include "defines.hpp"
#include "game.hpp"
#include "ship.hpp"
#include "../islands/island.hpp"
#include "../islands/island_buffer.hpp"
#include "../scenes/scene_manager.hpp"

namespace Game
{
    Ship ship;
    Vec2 gravity = Vec2{0.0, GravityAcceleration};

    Pen clearColor = {200, 200, 200};

    std::list<std::unique_ptr<IsLand>> islands;

    State gameState = {State::Boot};

    IslandBuffer buffer;

    // The scenes to be managed by the SceneManager.
    // Any scene that is running is removed from the collection
    // and handed over to the SceneManager. Once the scene has
    // exited the stage it is handed back the collection
    // --unless the scene is to be destroyed. For example, once the
    // BootScene is done it is destroyed meaning it isn't added
    // back to the collection.

    SceneManager sceneMan;

} // namespace Game
