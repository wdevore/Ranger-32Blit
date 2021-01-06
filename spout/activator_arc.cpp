#include <iostream>

#include "utilities.hpp"
#include "activator_arc.hpp"

ActivatorArc::ActivatorArc()
{
    minLife = 2.0;
    maxLife = 5.0;
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
    float speed = minSpeed + maxSpeed * drand48();

    particle->setVelocity(direction, speed);
}