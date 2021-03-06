#include <iostream>

#include "scene.hpp"

namespace Game
{
    Scene::Scene(std::string name)
    {
        this->name = name;
    }

    void Scene::update(uint32_t time)
    {
    }

    void Scene::render()
    {
    }

    std::string Scene::Name()
    {
        return name;
    }

    void Scene::enterScene()
    {
    }

    void Scene::exitScene()
    {
    }

    std::string Scene::nextScene()
    {
        return "";
    }

    bool Scene::shouldDispose()
    {
        return disposeOnExit;
    }

    SceneState Scene::CurrentState()
    {
        return state;
    }

    std::string Scene::toString()
    {
        return "id: (" + name + ")";
    }

} // namespace Game
