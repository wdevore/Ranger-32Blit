#pragma once

#include "32blit.hpp"

#include "particle_node.hpp"

using namespace blit;

namespace Game
{
    class ParticleActivator
    {
    protected:
        float startAngle;
        float endAngle;
        float minSpeed;
        float maxSpeed;
        float maxLife;

    public:
        ParticleActivator();
        // virtual ~ParticleActivator() = default;

        virtual void activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center) = 0;

        // NOTE: All methods need to be pure virtual. If not then you will need to define a .cpp file
        // with every non-pure method defined, even if they are empty.
        // In other words this class must be an "Interface" in order to exist without a .cpp file.
        void setMaxLifetime(float duration);
        void setStartAngle(float angle);
        void setEndAngle(float angle);
    };
} // namespace Game