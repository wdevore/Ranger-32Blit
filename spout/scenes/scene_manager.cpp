#include <iostream>

#include "scene_manager.hpp"

namespace Game
{
    SceneManager::SceneManager()
    {
    }

    void SceneManager::init()
    {
        std::cout << "SceneManager::init" << std::endl;
    }

    bool SceneManager::update(uint32_t time)
    {
        // If running scene is null then we need to pop one from the stack to run.
        if (!runningScene)
        {
            // std::cout << "Popping from stack" << std::endl;
            bool scenePopped = popScene();
            if (scenePopped)
            {
                std::cout << "Popped '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->init();
            }
            else
                return false;
        }

        bool finished = runningScene->update(time);

        if (finished)
        {
            std::cout << "Scene '" << runningScene->Name() << "' finished" << std::endl;
            if (!runningScene->shouldDispose())
            {
                std::cout << "Returning scene '" << runningScene->Name() << "' too pool" << std::endl;
                pool[runningScene->Name()] = std::move(runningScene);
            }

            bool scenePopped = popScene();

            if (scenePopped)
            {
                std::cout << "Popped another scene '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->init();
            }
            else
                return false;
        }

        return true;
    }

    void SceneManager::render()
    {
        if (runningScene)
            runningScene->render();
    }

    void SceneManager::addScene(std::unique_ptr<Scene> scene)
    {
        // std::cout << "SceneManager::addScene" << std::endl;

        pool[scene->Name()] = std::move(scene);

        // for (const auto &[name, scn] : pool)  // <-- C++17 syntax
        // std::cout << "added A ---------------" << std::endl;
        // for (const auto &element : pool)
        //     std::cout << element.first << std::endl;
        // std::cout << "added B ---------------" << std::endl;
    }

    void SceneManager::pushScene(std::string name)
    {
        std::cout << "SceneManager::pushScene '" << name << "'" << std::endl;

        stack.push(std::move(pool[name]));
        pool.erase(name);

        // std::cout << "~~~~~~~~~~~~~~~" << std::endl;
        // std::cout << stack.top()->Name() << std::endl;
        // std::cout << "pool ---------------" << std::endl;
        // for (const auto &element : pool)
        //     std::cout << element.first << std::endl;
    }

    bool SceneManager::popScene()
    {
        std::cout << "SceneManager::popScene" << std::endl;

        if (stack.empty())
        {
            return false; // Signal no more scenes to run
        }

        // std::unique_ptr<Scene> &top = stack.top();

        // Move the scene from the stack back into the pool but only
        // if the dispose flag is false.
        // if (!top->shouldDispose())
        // {
        //     pool[name] = std::move(top);
        // }

        runningScene = std::move(stack.top());
        // Clear scene reference left on stack.
        stack.pop();

        return true;

        // for (const auto &element : pool)
        //     std::cout << element.first << std::endl;
    }

} // namespace Game
