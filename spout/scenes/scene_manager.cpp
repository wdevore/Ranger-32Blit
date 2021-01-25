#include <iostream>

#include "scene_manager.hpp"

namespace Game
{
    SceneManager::SceneManager()
    {
    }

    void SceneManager::init()
    {
        // std::cout << "SceneManager::init" << std::endl;
    }

    bool SceneManager::update(uint32_t time)
    {
        // If running scene is null then we need to pop one from the stack to run.
        if (!runningScene)
        {
            bool scenePopped = pop();
            if (scenePopped)
            {
                // std::cout << "Popped '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->enterScene();
            }
            else
            {
                std::cout << "Atleast one Scene must have been queued" << std::endl;
                return false;
            }
        }

        runningScene->update(time);

        switch (runningScene->CurrentState())
        {
        case SceneState::Exit:
        {
            // std::cout << "Scene '" << runningScene->Name() << "' finished" << std::endl;

            // Before the running scene leaves
            // check to see if it recommends another scene to queue/run.
            std::string nextScene = runningScene->nextScene();

            runningScene->exitScene();
            runningScene->update(time);

            if (!runningScene->shouldDispose())
            {
                // std::cout << "Returning scene '" << runningScene->Name() << "' too pool" << std::endl;
                pool[runningScene->Name()] = std::move(runningScene);
            }

            if (!nextScene.empty())
            {
                // std::cout << "Next scene '" << nextScene << "'" << std::endl;
                // Scenes only run if they are placed on the stack, even if they are
                // immediately popped.
                queue(nextScene);
            }

            if (pop())
            {
                // std::cout << "Popped another scene '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->enterScene();
                return true;
            }
            else
                return false;
        }
        break;

        default:
            // std::cout << "Unknown scene state" << std::endl;
            break;
        }

        return true;
    }

    void SceneManager::render()
    {
        if (runningScene)
        {
            // std::cout << "Rending running scene" << std::endl;
            runningScene->render();
        }
    }

    void SceneManager::add(std::unique_ptr<Scene> scene)
    {
        pool[scene->Name()] = std::move(scene);
    }

    void SceneManager::queue(std::string name)
    {
        // std::cout << "SceneManager::queue '" << name << "'" << std::endl;

        stack.push(std::move(pool[name]));
        // The pool still contains slot where the scene used to be (i.e. nullptr) --remove it.
        pool.erase(name);
    }

    bool SceneManager::pop()
    {
        // std::cout << "SceneManager::pop" << std::endl;

        if (stack.empty())
        {
            std::cout << "SceneManager::pop no more scenes" << std::endl;
            return false; // Signal no more scenes to run
        }

        runningScene = std::move(stack.top());

        // Clear scene reference left on stack.
        stack.pop();

        return true;
    }

    std::string SceneManager::toString()
    {
        std::string s;
        s += "Stack:----------------\n";
        for (const auto &element : stack)
        {
            // std::cout << element->Name() << std::endl;
            s += element->Name() + "\n";
        }

        s += "Pool:----------------\n";
        // for (const auto &[name, scn] : pool)  // <-- C++17 syntax
        for (const auto &element : pool)
        {
            // std::cout << element.first << std::endl;
            s += element.first + "\n";
        }
        s += "-----------------------\n";

        return s;
    }

} // namespace Game
