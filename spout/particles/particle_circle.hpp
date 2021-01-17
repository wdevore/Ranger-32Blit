#include "particle_node.hpp"

namespace Game
{
    class ParticleCircle : public ParticleNode
    {
    private:
        Pen color;

    public:
        ParticleCircle() = default;
        ParticleCircle(int id);

        // We must override the pure virtual functions even though
        // ParticleNode has implementations for them.
        void update(uint32_t time) override;
        void render() override;

        void setColor(Pen color) override;
    };
} // namespace Game