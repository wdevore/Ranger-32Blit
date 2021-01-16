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

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;
    };

} // namespace Game