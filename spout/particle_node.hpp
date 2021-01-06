#pragma once

#include "32blit.hpp"

using namespace blit;

class ParticleNode
{
public:
    int id;

protected:
    Vec2 position;
    Vec2 velocity;
    uint32_t lifespan; // Life span
    bool active;
    uint32_t elapsed;

public:
    ParticleNode() = default;
    ParticleNode(int id);

    void setPosition(float x, float y);
    void setLifeSpan(float duration);
    void setActive(bool active);
    bool isActive();

    void setVelocity(float angle, float speed);
    void addForce(const Vec2 &force);

    virtual void update(uint32_t time) = 0;
    virtual void render() = 0;

    void reset();

    std::string toString();
};
