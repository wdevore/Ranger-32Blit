#include <memory>
#include <stack>
#include <unordered_map>

#include "scene.hpp"

namespace Game
{
    template <typename T, typename Container = std::deque<T>>
    class iterable_stack
        : public std::stack<T, Container>
    {
        using std::stack<T, Container>::c;

    public:
        // expose just the iterators of the underlying container
        auto begin() { return std::begin(c); }
        auto end() { return std::end(c); }

        auto begin() const { return std::begin(c); }
        auto end() const { return std::end(c); }
    };

    // The scenes to be managed by the SceneManager.
    // Any scene that is running is removed from the collection
    // and handed over to the SceneManager. Once the scene has
    // exited the stage it is handed back the collection
    // --unless the scene is to be destroyed. For example, once the
    // BootScene is done it is destroyed meaning it isn't added
    // back to the collection.

    class SceneManager
    {
    private:
        // Scenes running.
        iterable_stack<std::unique_ptr<Scene>> stack;

        // Pool of scenes that can be pushed and popped off the stack.
        std::unordered_map<std::string, std::unique_ptr<Scene>> pool;

        std::unique_ptr<Scene> runningScene;

    public:
        SceneManager();

        void add(std::unique_ptr<Scene> scene);

        void queue(std::string name);
        bool pop();

        void init();
        bool update(uint32_t time);
        void render();

        std::string toString();
    };

} // namespace Game