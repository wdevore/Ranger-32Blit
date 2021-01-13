#include "scene.hpp"

namespace Game
{
    class BootScene : public Scene
    {
    private:
    public:
        BootScene(std::string scName);

        void init() override;
        bool update(uint32_t time) override;
        void render() override;
    };

} // namespace Game