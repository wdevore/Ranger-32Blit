#include <memory>
#include <stack>
#include <unordered_map>

#include "scene.hpp"

namespace Game
{
    class SceneManager
    {
    private:
        // Scenes running.
        std::stack<std::unique_ptr<Scene>> stack;

        // Pool of scenes that can be pushed and popped off the stack.
        std::unordered_map<std::string, std::unique_ptr<Scene>> pool;

        std::unique_ptr<Scene> runningScene;

    public:
        SceneManager();

        void addScene(std::unique_ptr<Scene> scene);

        void pushScene(std::string name);
        bool popScene();

        void init();
        bool update(uint32_t time);
        void render();
    };

} // namespace Game