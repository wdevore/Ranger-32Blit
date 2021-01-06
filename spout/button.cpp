#include <iostream>

#include "button.hpp"

BlitButton::BlitButton(Button id)
{
    this->id = id;
    keyPressed = false;
}

void BlitButton::update()
{
    if (buttons.pressed & id && !keyPressed)
    {
        keyPressed = true;
    }
    
    if (buttons.released & id)
    {
        keyPressed = false;
    }
}

bool BlitButton::tapped()
{
    bool t = keyPressed;
    keyPressed = false;
    return t;
}

bool BlitButton::pressed()
{
    return keyPressed;
}

bool BlitButton::released()
{
    return keyPressed;
}
