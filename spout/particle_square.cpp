#include <iostream>

#include "32blit.hpp"

#include "particle_square.hpp"

ParticleSquare::ParticleSquare(int id)
{
    this->id = id;
    body.w = 2;
    body.h = 2;
    color = {64, 64, 64};
}

void ParticleSquare::update(uint32_t time)
{
    // std::cout << "ParticleSquare::update" << std::endl;
    ParticleNode::update(time);

    if (active) {
        // Check against display bounds. Bounce particle off wall.
        if (position.y >= screen.bounds.h) {
            position.y = screen.bounds.h-1;
            velocity.y *= -0.8;
        }
        else if (position.y <= 0) {
            position.y = 1;
            velocity.y *= -0.8;
        }

        if (position.x >= screen.bounds.w) {
            position.x = screen.bounds.w-1;
            velocity.x *= -0.8;
        }
        else if (position.x <= 0) {
            position.x = 1;
            velocity.x *= -0.8;
        }
    }
}

void ParticleSquare::render()
{
    // Draw body
    screen.pen = color;
    body.x = int32_t(float(position.x) - float(body.w) / 2.0 + 0.5);
    body.y = int32_t(float(position.y) - float(body.h) / 2.0 + 0.5);
    screen.rectangle(body);
}
