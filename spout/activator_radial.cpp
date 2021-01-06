#include <iostream>

#include "activator_radial.hpp"

void ActivatorRadial::activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center)
{
    ParticleActivator::activate(particle, center);

    float direction = 360.0 * drand48();
    float speed = maxSpeed * drand48();
    // std::cout << "direction: " << direction << ", speed: " << speed << std::endl;

    particle->setVelocity(direction, speed);
}
