#include <iostream>

#include "utilities.hpp"
#include "activator_arc.hpp"

ActivatorArc::ActivatorArc()
{
    minLife = 2.0;
    maxLife = 3.0;
    minAngularVelocity = 5.0;
    maxAngularVelocity = 15.0;
    minForce = 15.0;
    maxForce = 30.0;
    startAngle = DegreeToRadians * 175.0;
    endAngle = DegreeToRadians * 185.0;
}

void ActivatorArc::activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center)
{
    ParticleActivator::activate(particle, center);
    // std::cout << "startAngle: " << startAngle << ", endAngle: " << endAngle << std::endl;

    float direction = lerp(startAngle, endAngle, drand48());
    float speed = maxSpeed * drand48();

    particle->setVelocity(direction, speed);

    float angularVel = lerp(minAngularVelocity, maxAngularVelocity, drand48());
    if (drand48() < 0.5)
        angularVel = -angularVel;

    float upForce = lerp(minForce, maxForce, drand48());
}
