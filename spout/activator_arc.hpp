#include "particle_activator.hpp"
#include "particle_node.hpp"

namespace Game
{
    class ActivatorArc : public ParticleActivator
    {
    private:
        float minLife;
        float minAngularVelocity;
        float maxAngularVelocity;
        float minForce;
        float maxForce;

    public:
        ActivatorArc();

        void activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center) override;
    };
} // namespace Game