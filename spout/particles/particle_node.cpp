#include <iostream>

#include "32blit.hpp"

#include "particle_node.hpp"

using namespace blit;

namespace Game
{
    ParticleNode::ParticleNode(int id)
    {
        this->id = id;
        active = false;
        elapsed = 0;
    }

    int ParticleNode::Id()
    {
        return id;
    }
    
    void ParticleNode::setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    float ParticleNode::posX()
    {
        return position.x;
    }

    float ParticleNode::posY()
    {
        return position.y;
    }

    void ParticleNode::setLifeSpan(float duration)
    {
        lifespan = duration;
    }

    void ParticleNode::setActive(bool active)
    {
        this->active = active;
    }

    bool ParticleNode::isActive()
    {
        return this->active;
    }

    void ParticleNode::setVelocity(float angle, float speed)
    {
        velocity.x = 0.0;
        velocity.y = -speed;
        velocity.rotate(-angle);
    }

    void ParticleNode::addForce(const Vec2 &force)
    {
        velocity += force;
    }

    void ParticleNode::update(uint32_t time)
    {

        elapsed += time;
        active = elapsed < lifespan;

        // Update ParticleNode's position as long as the ParticleNode is active.
        if (active)
        {
            position += velocity;
        }
    }

    void ParticleNode::render()
    {
    }

    void ParticleNode::reset()
    {
        active = false;
        elapsed = 0;
    }

    void ParticleNode::setCollided(bool collide)
    {
        this->collide = collide;
    }

    // std::ostream& operator<<(std::ostream &strm, const std::unique_ptr<ParticleNode> &n) {
    //   return strm << "id (" << n->id << ")";
    // }

    std::string ParticleNode::toString()
    {
        return "id: (" + std::to_string(id) + ")";
    }
} // namespace Game