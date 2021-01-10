#include <iostream>
#include <list>

#include "defines.hpp"
#include "ship.hpp"
#include "../particles/activator_arc.hpp"
#include "../particles/particle_square.hpp"
#include "../islands/island.hpp"

#define BodySize (int32_t)2

namespace Game
{
    extern std::list<std::unique_ptr<IsLand>> islands;

    void Ship::init()
    {
        // Place ship
        reset();

        thrustColor = {255, 255, 255};
        bodyColor = {0, 0, 0};

        particleGravity = Vec2{0.0, 0.015};

        activator = std::make_unique<ActivatorArc>();

        // Set up thrust particles
        for (size_t i = 0; i < MaxThrustParticles; i++)
        {
            ps.addParticle(std::make_unique<ParticleSquare>(i));
        }
    }

    void Ship::destroy()
    {
        ps.destroy();
        std::cout << "Ship destroyed." << std::endl;
    }

    ParticleSystem &Ship::particleThrust()
    {
        return ps;
    }

    void Ship::reset()
    {
        rotation = 0.0;
        died = false;
        position.x = screen.bounds.w / 2;
        position.y = screen.bounds.h / 2;
        velocity.x = 0.0;
        velocity.y = 0.0;
    }

    void Ship::rotateCW()
    {
        rotational_velocity -= pi / 720.0 / RotationalRate;
    }

    void Ship::rotateCCW()
    {
        rotational_velocity += pi / 720.0 / RotationalRate;
    }

    void Ship::applyThrust(bool thrust)
    {
        this->thrust = thrust;

        direction.x = 0.0;
        direction.y = 0.0;

        if (thrust)
        {
            // Subtract such that the ship moves forward.
            direction.y = -ShipAcceleration;

            ps.setPosition(position.x, position.y);
            ps.triggerOneShot(activator);
        }

        direction.rotate(-rotation);
    }

    bool Ship::thrusting()
    {
        return thrust;
    }

    void Ship::update(uint32_t time, Vec2 &force)
    {
        using namespace Game;

        // Update Velocity
        velocity += (direction + force) * ShipDeceleration;
        if (velocity.y > MaxDownwardVelocity)
            velocity.y = MaxDownwardVelocity;
        if (velocity.y < -MaxUpwardVelocity)
            velocity.y = -MaxUpwardVelocity;
        // std::cout << velocity.y << std::endl;

        // Update position based on velocity
        position += velocity;

        // Update angular speed
        rotational_velocity *= ShipRotationalDeceleration;
        rotation += rotational_velocity;

        activator->setStartAngle(rotation + (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));
        activator->setEndAngle(rotation - (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));

        // Check for scrolling

        if (position.y < Spout_ScrollLine)
        {
            position.y = Spout_ScrollLine + 0.5;
            tripped = true;
        }
        else
        {
            tripped = false;
        }

        // Ship explodes if it falls below the bottom.
        if (position.y > screen.bounds.h)
        {
            // std::cout << "BOOM!" << std::endl;
            died = true;
        }

        // Prevent ship from going beyond the left/right walls
        if (position.x >= (screen.bounds.w - BodySize))
        {
            position.x = screen.bounds.w - BodySize - 0.5;
        }

        if (position.x <= 0.0 + BodySize)
        {
            position.x = BodySize + 0.5;
        }

        ps.setPosition(float(int(position.x)), float(int(position.y)));
        ps.addForce(particleGravity);

        ps.update(time);

        pY = position.y;
    }

    void Ship::render()
    {
        // Draw thrust vector line
        screen.pen = thrustColor;
        thrust_vector.x = 0;
        thrust_vector.y = -ThrustEngineSize;
        thrust_vector.rotate(-rotation);
        screen.line(position, position - thrust_vector);

        ps.render();

        // Draw body
        screen.pen = collide ? collideColor : bodyColor;
        screen.circle(position, BodySize);
    }

    bool Ship::hitTripWire()
    {
        return tripped;
    }

    float Ship::posX()
    {
        return position.x;
    }

    float Ship::posY()
    {
        return position.y;
    }

    void Ship::setCollided(bool collide)
    {
        this->collide = collide;
    }

    bool Ship::isDead()
    {
        return died;
    }

    void Ship::debug()
    {
        if (!debugF)
        {
            // debugF = true;
            // ps.setAutoTrigger(true);
            // activator->setStartAngle(rotation + (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));
            // activator->setEndAngle(rotation - (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));

            // ps.setPosition(position.x, position.y);
            // ps.triggerOneShot(activator);
            // ps.triggerExplosion(activator);
        }
    }
} // namespace Game