#include "32blit.hpp"

#include "particle_system.hpp"

using namespace blit;

#define ShipAcceleration (float)0.01
#define ShipDeceleration (float)0.8
#define ShipRotationalDeceleration (float)0.95
#define ThrustEngineSize (float)8

// The Ship
class Ship
{
private:
    // Speed and magnitude
    Vec2 velocity;
    Vec2 position;

    float rotation = 0;
    float rotational_velocity = 0;

    Vec2 thrust_vector;
    bool thrust = false;
    Vec2 direction;

    Vec2 particleGravity;

    Pen thrustColor;
    Pen bodyColor;

    ParticleSystem ps;
    std::unique_ptr<ParticleActivator> activator;

    bool debugF = false;

public:
    void init();
    void destroy();

    void reset();

    void rotateCW();
    void rotateCCW();

    void applyThrust(bool thrust);
    bool thrusting();

    void update(uint32_t time, Vec2 &force);
    void render();

    void debug();
};
