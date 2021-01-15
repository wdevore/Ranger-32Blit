#include "scene.hpp"

namespace Game
{
    class SplashScene : public Scene
    {
    private:
    public:
        SplashScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void EnterScene() override;
        void ExitScene() override;
        std::string NextScene() override;
    };

} // namespace Game