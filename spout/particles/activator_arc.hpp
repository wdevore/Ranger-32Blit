#include "particle_activator.hpp"
#include "particle_node.hpp"

namespace Game
{
    class ActivatorArc : public ParticleActivator
    {
    private:
        float minAngularVelocity;
        float maxAngularVelocity;

    public:
        ActivatorArc();

        void activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center) override;
    };
} // namespace Game