#include "ngl/VAOPrimitives.h"
#include "Particle.h"

void Particle::addForce(ngl::Vec3 force)
{
    m_acceleration += force / m_mass;
}

void Particle::applyGravity(const float gravityValue)
{
    addForce(ngl::Vec3(0.0f, -gravityValue, 0.0f));
}

void Particle::offsetPosition(const ngl::Vec3 offset, bool ignorePinned)
{
    if (m_isMovable || ignorePinned)
    {
        m_pos += offset;
    }
}

void Particle::addToNormal(ngl::Vec3 normal)
{
    normal.normalize();
    m_accumulatedNormal += normal;
}

void Particle::timeStep(const float damping, const float stepSize)
{
    if (!m_isMovable)
    {
        return;
    }
    float stepSize2 = stepSize * stepSize;

    ngl::Vec3 storedPos = m_pos;
    m_pos += (m_pos - m_oldPos) * (1.0f - damping) + m_acceleration * stepSize2;
    m_oldPos = storedPos;
    resetAcceleration();
}

void Particle::drawSphere() const
{
    ngl::VAOPrimitives::draw("particleSphere");
}