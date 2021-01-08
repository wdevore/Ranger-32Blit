#include "particle_node.hpp"

namespace Game
{
    class Button
    {
    private:
        bool keyPressed = false;
        blit::Button id;

    public:
        Button() = default;
        Button(blit::Button id);

        void update();

        bool tapped();

        bool pressed();
        bool released();
    };

} // namespace Game