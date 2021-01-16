#include "scene.hpp"

namespace Game
{
    class ExitScene : public Scene
    {
    private:
    public:
        ExitScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;
    };

} // namespace Game