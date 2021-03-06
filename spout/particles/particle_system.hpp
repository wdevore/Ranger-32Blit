#pragma once

#include <list>
#include "32blit.hpp"

#include "particle_node.hpp"
#include "particle_activator.hpp"

using namespace blit;

namespace Game
{
    class ParticleSystem
    {
    private:
        int id;
        Vec2 epiCenter;

        bool active;
        bool autoTrigger;

        std::list<std::unique_ptr<ParticleNode>> particles;

    public:
        ParticleSystem() = default;
        ParticleSystem(int id);

        int Id();

        void destroy();

        void addParticle(std::unique_ptr<ParticleNode> p);
        std::list<std::unique_ptr<ParticleNode>> &getParticles();

        void setPosition(float x, float y);
        void setAutoTrigger(bool enable);
        void setActive(bool active);
        bool isActive();

        void update(uint32_t time);
        void render();

        void addForce(const Vec2 &force);

        void triggerOneShot(std::unique_ptr<ParticleActivator> &activator);
        void triggerAt();
        void triggerExplosion(std::unique_ptr<ParticleActivator> &activator);

        void reset();
    };
} // namespace Game