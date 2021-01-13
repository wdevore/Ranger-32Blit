#include "scene.hpp"

namespace Game
{
    class SplashScene : public Scene
    {
    private:
    public:
        SplashScene(std::string scName);

        void init() override;
        bool update(uint32_t time) override;
        void render() override;
    };

} // namespace Game