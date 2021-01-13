#include <iostream>

#include "scene_game.hpp"

namespace Game
{
    GameScene::GameScene(std::string name) : Scene{name}
    {
    }

    void GameScene::init()
    {
    }

    bool GameScene::update(uint32_t time)
    {
        return false;
    }

    void GameScene::render()
    {
    }

} // namespace Game
