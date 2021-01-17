#include <iostream>

#include "32blit.hpp"

#include "particle_system.hpp"

using namespace blit;

namespace Game
{
    ParticleSystem::ParticleSystem()
    {
        active = false;
        autoTrigger = false;
    }

    void ParticleSystem::destroy()
    {
        // std::cout << "ParticleSystem destroyed" << std::endl;
    }

    void ParticleSystem::addParticle(std::unique_ptr<ParticleNode> p)
    {
        particles.push_back(std::move(p));
    }

    std::list<std::unique_ptr<ParticleNode>> &ParticleSystem::getParticles()
    {
        return particles;
    }

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

    bool ParticleSystem::isActive()
    {
        return active;
    }

    void ParticleSystem::addForce(const Vec2 &force)
    {
        if (active)
        {
            for (auto &p : particles)
            {
                if (p->isActive())
                {
                    p->addForce(force);
                }
            }
        }
    }

    void ParticleSystem::update(uint32_t time)
    {
        if (active)
        {
            active = false;
            for (auto &p : particles)
            {
                if (p->isActive())
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

    void ParticleSystem::reset()
    {
        for (auto &p : particles)
            p->reset();
    }

} // namespace Game