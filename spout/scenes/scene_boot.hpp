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

        void enterScene() override;
        void exitScene() override;
    };

} // namespace Game