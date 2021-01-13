#include "scene.hpp"

namespace Game
{
    class GameScene : public Scene
    {
    private:
    public:
        GameScene(std::string scName);

        void init() override;
        bool update(uint32_t time) override;
        void render() override;
    };

} // namespace Game