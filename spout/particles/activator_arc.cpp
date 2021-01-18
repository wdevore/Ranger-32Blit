#include <iostream>

#include "../game/defines.hpp"
#include "activator_arc.hpp"

namespace Game
{
    extern float randF();

    ActivatorArc::ActivatorArc()
    {
        minLife = 2.0;
        maxLife = 5.0;
        minAngularVelocity = 5.0;
        maxAngularVelocity = 15.0;
        minForce = 15.0;
        maxForce = 30.0;
        startAngle = Game::DegreeToRadians * 175.0;
        endAngle = Game::DegreeToRadians * 185.0;
    }

    void ActivatorArc::activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center)
    {
        ParticleActivator::activate(particle, center);
        // std::cout << "startAngle: " << startAngle << ", endAngle: " << endAngle << std::endl;

        float direction = Game::lerp(startAngle, endAngle, randF());
        float speed = minSpeed + maxSpeed * randF();

        particle->setVelocity(direction, speed);
    }
} // namespace Game