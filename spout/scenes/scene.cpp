#include <iostream>

#include "scene.hpp"

namespace Game
{
    Scene::Scene(std::string name)
    {
        this->name = name;
    }

    void Scene::init()
    {
    }

    bool Scene::update(uint32_t time)
    {
        return true;
    }

    void Scene::render()
    {
    }

    std::string Scene::Name()
    {
        return name;
    }

    bool Scene::shouldDispose()
    {
        return disposeOnExit;
    }

    std::string Scene::toString()
    {
        return "id: (" + name + ")";
    }

} // namespace Game
