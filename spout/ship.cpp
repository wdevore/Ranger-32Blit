#include <iostream>

#include "utilities.hpp"
#include "ship.hpp"
#include "activator_arc.hpp"
// #include "activator_radial.hpp"
#include "particle_node.hpp"
#include "particle_square.hpp"

#define BodySize (int32_t)2

void Ship::init()
{
    // Place ship just below center
    position = Vec2(screen.bounds.w / 2, screen.bounds.h / 1.5);
    rotation = 0.0;

    thrustColor = {255, 255, 255};
    bodyColor = {0, 0, 0};

    particleGravity = Vec2{0.0, 0.015};

    activator = std::make_unique<ActivatorArc>();

    // Set up thrust particles
    for (size_t i = 0; i < 200; i++)
    {
        ps.addParticle(std::make_unique<ParticleSquare>(i));
    }
}

void Ship::destroy()
{
    ps.destroy();
    std::cout << "Ship destroyed." << std::endl;
}

void Ship::reset()
{
    position.x = screen.bounds.w / 2;
    position.y = screen.bounds.h / 1.5;
    velocity.x = 0.0;
    velocity.y = 0.0;
}

void Ship::rotateCW()
{
    rotational_velocity -= pi / 720;
}

void Ship::rotateCCW()
{
    rotational_velocity += pi / 720;
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
    // Update Velocity
    velocity += (direction + force) * ShipDeceleration;

    // Update position based on velocity
    position += velocity;

    // Update angular speed
    rotational_velocity *= ShipRotationalDeceleration;
    rotation += rotational_velocity;

    activator->setStartAngle(rotation + (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));
    activator->setEndAngle(rotation - (DegreeToRadians * 5.0) + (DegreeToRadians * 180.0));

    // Check for scrolling
    if (position.y >= screen.bounds.h / 2 && position.y < screen.bounds.h / 1.8)
    {
        std::cout << "scrolling..." << std::endl;
    }

    // Ship explodes if it falls below the bottom.
    if (position.y > screen.bounds.h)
    {
        std::cout << "BOOM!" << std::endl;
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
    screen.pen = bodyColor;
    screen.circle(position, BodySize);
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