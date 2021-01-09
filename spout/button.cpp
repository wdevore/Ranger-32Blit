#include <iostream>

#include "button.hpp"

namespace Game
{
    Game::Button::Button(blit::Button id)
    {
        this->id = id;
        keyPressed = false;
    }

    void Game::Button::update()
    {
        if (blit::buttons.pressed & id && !keyPressed)
        {
            keyPressed = true;
        }

        if (blit::buttons.released & id)
        {
            keyPressed = false;
        }
    }

    bool Game::Button::tapped()
    {
        bool t = keyPressed;
        keyPressed = false;
        return t;
    }

    bool Game::Button::pressed()
    {
        return keyPressed;
    }

    bool Game::Button::released()
    {
        return keyPressed;
    }

} // namespace Game