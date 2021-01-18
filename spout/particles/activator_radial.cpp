#include <iostream>

#include "activator_radial.hpp"

namespace Game
{
    extern float randF();

    ActivatorRadial::ActivatorRadial()
    {
        minLife = 2.0;
        maxLife = 5.0;
        minForce = 15.0;
        maxForce = 30.0;
    }

    void ActivatorRadial::activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center)
    {
        ParticleActivator::activate(particle, center);

        float direction = 360.0 * randF();
        float speed = minSpeed + maxSpeed * randF();
        // std::cout << "direction: " << direction << ", speed: " << speed << std::endl;

        particle->setVelocity(direction, speed);
    }
} // namespace Game