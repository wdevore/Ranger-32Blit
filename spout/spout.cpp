#include <iostream>

#include "spout.hpp"
#include "graphics/color.hpp"
#include "types/vec2.hpp"

// Forward declares
void draw_stats(uint32_t ms_start, uint32_t ms_end);

using namespace blit;

#define ShipAcceleration (float)0.02
#define ShipDeceleration (float)0.99
#define ShipRotationalDeceleration (float)0.95
#define GravityAcceleration (float)0.005
#define ThrustEngineSize (float)10

// The Ship
struct Ship
{
    // Speed and magnitude
    Vec2 velocity;
    Vec2 position;
    float rotation = 0;
    float rotational_velocity = 0;
    Vec2 thrust_vector;
    bool thrust = false;
};

Ship ship;
Vec2 gravity;
Vec2 direction(0, 0);

// -----------------------------------------------------------------
// Intialize
// -----------------------------------------------------------------
void init()
{
    set_screen_mode(ScreenMode::hires);

    // Place ship just below center
    ship.position = Vec2(screen.bounds.w / 2, screen.bounds.h / 1.5);

    gravity.x = 0.0;
    gravity.y = GravityAcceleration;
}

// -----------------------------------------------------------------
// Update state
// -----------------------------------------------------------------
void update(uint32_t time)
{
    // "2" on keyboard
    if (pressed(Button::MENU))
    {
        exit(0);
    }

    // "1" on keyboard
    if (pressed(Button::HOME))
    {
        ship.position.x = screen.bounds.w / 2;
        ship.position.y = screen.bounds.h / 1.5;
        ship.velocity.x = 0.0;
        ship.velocity.y = 0.0;
    }

    // -----------------------------------------
    // Rotate
    if (pressed(Button::DPAD_LEFT)) // "A" key
    {
        ship.rotational_velocity += pi / 720;
    }
    else if (pressed(Button::DPAD_RIGHT))
    {
        ship.rotational_velocity -= pi / 720;
    }

    // -----------------------------------------
    // Thrust
    ship.thrust = pressed(Button::A);

    direction.x = 0.0;
    direction.y = 0.0;

    // Button::A == "Z" key
    if (ship.thrust)
    {
        // Subtract such that the ship moves forward.
        direction.y -= ShipAcceleration;
    }

    direction.rotate(-ship.rotation);

    // Update Velocity
    ship.velocity += (direction + gravity) * ShipDeceleration;

    // Update position based on velocity
    ship.position += ship.velocity;

    // Update angular speed
    ship.rotational_velocity *= ShipRotationalDeceleration;
    ship.rotation += ship.rotational_velocity;

    if (ship.position.y > screen.bounds.h ||
        ship.position.x > screen.bounds.w ||
        ship.position.x < 0.0)
    {
        std::cout << "BOOM!" << std::endl;
    }
}

// -----------------------------------------------------------------
// Render
// -----------------------------------------------------------------
void render(uint32_t time)
{
    uint32_t ms_start = now();

    screen.pen = Pen(200, 200, 200);
    screen.clear();

    if (ship.thrust)
    {
    }

    // Draw thrust line
    screen.pen = Pen(255, 255, 255);
    ship.thrust_vector.x = 0;
    ship.thrust_vector.y = -ThrustEngineSize;
    ship.thrust_vector.rotate(-ship.rotation);
    screen.line(ship.position, ship.position - ship.thrust_vector);

    screen.pen = Pen(0, 0, 0);
    screen.circle(ship.position, 2);

    uint32_t ms_end = now();

    draw_stats(ms_start, ms_end);
}
