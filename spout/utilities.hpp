#pragma once
// #ifndef UTILITIES_H
// #define UTILITIES_H

#include "32blit.hpp"

namespace Game
{
    // Gravity is typically 0.001
    const float GravityAcceleration = 0.001;
    const float Pi = 3.1415926535897932384626433;
    const float DegreeToRadians = Pi / 180.0;

    const float MaxParticleLifetime = 2.0;
    const float MinParticleSpeed = 0.25;
    const float MaxParticleSpeed = 2.0;

// Because I need to reference screen bounds I can't use "const". Unfortunately
// this means the "define" isn't really in the Game namespace any longer.
#define Spout_ScrollLine (float(blit::screen.bounds.h) / 2.5)

    float lerp(float min, float max, float t);
} // namespace Game

// #endif /* !UTILITIES_H */
