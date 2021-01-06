#include "32blit.hpp"

#include "particle_node.hpp"
#include "particle_activator.hpp"

using namespace blit;

class ParticleSystem
{
private:
    Vec2 epiCenter;

    bool active;
    bool autoTrigger;

    // std::unique_ptr<ParticleActivator> activator;
    std::vector<std::unique_ptr<ParticleNode>> particles;

public:
    ParticleSystem();
    void destroy();

    void addParticle(std::unique_ptr<ParticleNode> p);
    // void setParticleActivator(std::unique_ptr<ParticleActivator> activator);

    void setPosition(float x, float y);
    void setAutoTrigger(bool enable);
    void setActive(bool active);

    void update(uint32_t time);
    void render();

    void triggerOneShot(std::unique_ptr<ParticleActivator> &activator);
    void triggerAt();
    void triggerExplosion(std::unique_ptr<ParticleActivator> &activator);
};
