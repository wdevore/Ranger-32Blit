#include <iostream>

#include "32blit.hpp"

#include "particle_system.hpp"

using namespace blit;

ParticleSystem::ParticleSystem()
{
    active = false;
    autoTrigger = false;
}

void ParticleSystem::destroy()
{
    std::cout << "ParticleSystem destroyed" << std::endl;
}

void ParticleSystem::addParticle(std::unique_ptr<ParticleNode> p)
{
    particles.push_back(std::move(p));
}

// void ParticleSystem::setParticleActivator(std::unique_ptr<ParticleActivator> activator)
// {
//     this->activator = std::move(activator);
// }

void ParticleSystem::setPosition(float x, float y)
{
    epiCenter.x = x;
    epiCenter.y = y;
}

void ParticleSystem::setAutoTrigger(bool enable)
{
    autoTrigger = enable;
}

void ParticleSystem::setActive(bool active)
{
    this->active = active;
}

void ParticleSystem::update(uint32_t time)
{
    if (active)
    {
        active = false;
        for (auto &p : particles)
        {
            if (!p->isActive())
            {
                // std::cout << "ps !active: " << time << ", " << p->toString() << std::endl;
                // if (autoTrigger)
                //     triggerOneShot();
            }
            else
            {
                // std::cout << "ps active: " << time << ", " << p->toString() << std::endl;
                p->update(time);
                // Keep system alive until all particles have died.
                active = true;
            }
        }
    }
}

void ParticleSystem::render()
{
    if (active)
    {
        for (auto &p : particles)
        {
            if (p->isActive())
                p->render();
        }
    }
}

void ParticleSystem::triggerOneShot(std::unique_ptr<ParticleActivator> &activator)
{
    active = true;

    // Look for a dead particle to resurrect.
    for (auto &p : particles)
    {
        if (!p->isActive())
        {
            // std::cout << "triggerOneShot activate: " << p->toString() << std::endl;
            activator->activate(p, epiCenter);
            break;
        }
    }
}

void ParticleSystem::triggerAt()
{
}

void ParticleSystem::triggerExplosion(std::unique_ptr<ParticleActivator> &activator)
{
    active = true;

    for (auto &p : particles)
        activator->activate(p, epiCenter);
}
