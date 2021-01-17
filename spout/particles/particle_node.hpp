#pragma once

#include "32blit.hpp"

using namespace blit;

namespace Game
{
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
        bool collide = false;

    public:
        ParticleNode() = default;
        ParticleNode(int id);

        void setPosition(float x, float y);
        float posX();
        float posY();

        void setLifeSpan(float duration);
        void setActive(bool active);
        bool isActive();

        void setVelocity(float angle, float speed);
        void addForce(const Vec2 &force);

        virtual void update(uint32_t time) = 0;
        virtual void render();

        virtual void setColor(Pen color) = 0;

        void setCollided(bool collide);
        
        void reset();

        std::string toString();
    };
} // namespace Game