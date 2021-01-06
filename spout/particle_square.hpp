#include "particle_node.hpp"

class ParticleSquare : public ParticleNode
{
    private:
    Rect body;
    Pen color;
    
public:
    ParticleSquare() = default;
    ParticleSquare(int id);

    // We must override the pure virtual functions even though
    // ParticleNode has implementations for them.
    void update(uint32_t time) override;
    void render() override;
};