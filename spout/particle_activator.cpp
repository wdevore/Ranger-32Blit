#include <iostream>

#include "32blit.hpp"

#include "utilities.hpp"
#include "particle_node.hpp"
#include "particle_activator.hpp"

using namespace blit;

ParticleActivator::ParticleActivator()
{
    using namespace Game;
    maxLife = MaxParticleLifetime;
    minSpeed = MinParticleSpeed;
    maxSpeed = MaxParticleSpeed;
}

void ParticleActivator::activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center)
{
    particle->setPosition(center.x, center.y);

    // A random lifetime ranging from 0.0 to max_life
    float lifespan = drand48() * maxLife * 1000.0;
    // std::cout << "lifespan: " << lifespan << std::endl;

    particle->setLifeSpan(lifespan);

    particle->reset();

    particle->setActive(true);
}

void ParticleActivator::setMaxLifetime(float duration)
{
    maxLife = duration;
}

void ParticleActivator::setStartAngle(float angle)
{
    startAngle = angle;
}

void ParticleActivator::setEndAngle(float angle)
{
    endAngle = angle;
}
