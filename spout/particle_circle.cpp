#include <iostream>

#include "particle_circle.hpp"

ParticleCircle::ParticleCircle(int id)
{
    this->id = id;
    color = {64, 64, 64};
}

void ParticleCircle::update(uint32_t time)
{
    // std::cout << "ParticleCircle::update" << std::endl;
    ParticleNode::update(time);
}

void ParticleCircle::render()
{
    // Draw body
    screen.pen = color;
    screen.circle(position, 3);
}
