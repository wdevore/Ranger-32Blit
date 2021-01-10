#include "particle_node.hpp"

namespace Game
{
    class ParticleSquare : public ParticleNode
    {
    private:
        Rect body;
        Pen color;
        Pen collideColor = {127, 127, 255};

    public:
        ParticleSquare() = default;
        ParticleSquare(int id);

        // We must override the pure virtual functions even though
        // ParticleNode has implementations for them.
        void update(uint32_t time) override;
        void render() override;
    };
} // namespace Game