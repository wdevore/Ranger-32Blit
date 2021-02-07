#pragma once
// #ifndef UTILITIES_H
// #define UTILITIES_H

#include "32blit.hpp"

namespace Game
{
    struct GameScore
    {
        char initials[3];
        int altitude;
        int score;
        int time;
    };

    struct GameSave
    {
        GameScore scores[5];
    };

    const int IslandXOffsetMin = -30;
    const int IslandXOffsetMax = 30;
    const int IslandVerticalDistToViewMin = 50;
    const int IslandVerticalDistToViewMax = 200;

    const int MineXOffsetMin = -30;
    const int MineXOffsetMax = 30;
    const int MineVerticalDistToViewMin = 100;
    const int MineVerticalDistToViewMax = 400;

    const int MaxExplosionParticles = 200;

    const int MaxThrustParticles = 150;
    const float MaxUpwardVelocity = 0.2;
    const float MaxDownwardVelocity = 0.3;
    const float MaxHorizontalVelocity = 0.6;
    const float GravityAcceleration = 0.00055;
    const float RotationalRate = 2.5; // How fast the ship rotates

    const float Pi = 3.1415926535897932384626433;
    const float DegreeToRadians = Pi / 180.0;

    const float MaxParticleLifetime = 2.0;
    const float MinParticleSpeed = 0.25;
    const float MaxParticleSpeed = 2.0;

// Because I need to reference screen bounds I can't use "const". Unfortunately
// this means the "define" isn't really in the Game namespace any longer.
#define Spout_ScrollLine (float(blit::screen.bounds.h) / 2.2)

    float lerp(float min, float max, float t);
} // namespace Game

// #endif /* !UTILITIES_H */
