#include "particle_activator.hpp"
#include "particle_node.hpp"

namespace Game
{
    // Generate particles in 360 degrees.
    class ActivatorRadial : public ParticleActivator
    {
    public:
        ActivatorRadial() = default;

        void activate(std::unique_ptr<ParticleNode> &particle, Vec2 &center) override;
    };
} // namespace Game