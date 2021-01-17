#include "scene.hpp"

namespace Game
{
    class AboutScene : public Scene
    {
    private:
    public:
        AboutScene(std::string scName);

        void update(uint32_t time) override;
        void render() override;

        void enterScene() override;
        void exitScene() override;
        std::string nextScene() override;
    };

} // namespace Game