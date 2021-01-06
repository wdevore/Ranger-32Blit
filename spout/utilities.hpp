#pragma once

// Gravity is typically 0.005
#define GravityAcceleration (float)0.005
#define Pi (float)3.1415926535897932384626433
#define DegreeToRadians (float)(Pi / 180.0)

#define MaxParticleLifetime (float)2.0
#define MaxParticleSpeed (float)2.0

float lerp(float min, float max, float t);
