#include "scene.hpp"

namespace Game
{
    class GameScene : public Scene
    {
    private:
    public:
        GameScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void EnterScene() override;
        void ExitScene() override;
        std::string NextScene() override;
    };

} // namespace Game