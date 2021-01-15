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
            bool scenePopped = pop();
            if (scenePopped)
            {
                std::cout << "Popped '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->EnterScene();
            }
            else
            {
                std::cout << "Atleast one Scene must have been queue" << std::endl;
                return false;
            }
        }

        runningScene->update(time);

        switch (runningScene->CurrentState())
        {
        case SceneState::Exit:
        {
            std::cout << "Scene '" << runningScene->Name() << "' finished" << std::endl;

            // Before the running scene leaves
            // check to see if it suggests another scene to queue/run.
            std::string nextScene = runningScene->NextScene();

            runningScene->ExitScene();
            runningScene->update(time);

            if (!runningScene->shouldDispose())
            {
                std::cout << "Returning scene '" << runningScene->Name() << "' too pool" << std::endl;
                pool[runningScene->Name()] = std::move(runningScene);
            }

            if (!nextScene.empty())
            {
                std::cout << "Next scene '" << nextScene << "'" << std::endl;
                queue(nextScene);
            }

            if (pop())
            {
                std::cout << "Popped another scene '" << runningScene->Name() << "' from stack" << std::endl;
                runningScene->EnterScene();
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
        // std::cout << "SceneManager::add" << std::endl;

        pool[scene->Name()] = std::move(scene);

        // for (const auto &[name, scn] : pool)  // <-- C++17 syntax
        // std::cout << "added A ---------------" << std::endl;
        // for (const auto &element : pool)
        //     std::cout << element.first << std::endl;
        // std::cout << "added B ---------------" << std::endl;
    }

    void SceneManager::queue(std::string name)
    {
        std::cout << "SceneManager::queue '" << name << "'" << std::endl;

        stack.push(std::move(pool[name]));
        pool.erase(name);

        // std::cout << "~~~~~~~~~~~~~~~" << std::endl;
        // std::cout << stack.top()->Name() << std::endl;
        // std::cout << "pool ---------------" << std::endl;
        // for (const auto &element : pool)
        //     std::cout << element.first << std::endl;
    }

    bool SceneManager::pop()
    {
        std::cout << "SceneManager::pop" << std::endl;

        if (stack.empty())
        {
            std::cout << "SceneManager::popScene no more scenes" << std::endl;
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
