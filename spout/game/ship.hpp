#pragma once

#include "32blit.hpp"

#include "../particles/particle_system.hpp"

using namespace blit;

#define ShipAcceleration (float)0.003
#define ShipDeceleration (float)5.0
#define ShipRotationalDeceleration (float)0.95
#define ThrustEngineSize (float)8

// The Ship
namespace Game
{
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
        Pen collideColor = {255, 127, 0};

        ParticleSystem ps;
        std::unique_ptr<ParticleActivator> activator;

        int score = 0;
        bool tripped = false;
        bool collide = false;
        bool died = false;
        float pY = 0.0;

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

        bool hitTripWire();

        float posX();
        float posY();

        int Score();
        void addToScore(int value);

        void setCollided(bool collide);
        ParticleSystem& particleThrust();
        
        bool isDead();
        void setAlive();

        void debug();
    };
} // namespace Game