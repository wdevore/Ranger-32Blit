#include "scene.hpp"

namespace Game
{
    class BootScene : public Scene
    {
    private:
    public:
        BootScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void EnterScene() override;
        void ExitScene() override;
    };

} // namespace Game