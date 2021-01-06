#include "particle_node.hpp"

class BlitButton
{
private:
    bool keyPressed = false;
    Button id;

public:
    BlitButton()=default;
    BlitButton(Button id);

    void update();

    bool tapped();

    bool pressed();
    bool released();
};
