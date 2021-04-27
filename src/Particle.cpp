#include "Particle.h"

void Particle::addForce(ngl::Vec3 force)
{
    m_acceleration += force / m_mass;
}

void Particle::offsetPosition(const ngl::Vec3 offset)
{
    if (m_isMovable)
    {
        m_pos += offset;
    }
}

void Particle::addToNormal(ngl::Vec3 normal)
{
    normal.normalize();
    m_accumulatedNormal += normal;
}

void Particle::timeStep(const float damping, float stepSize)
{
    if (!m_isMovable)
    {
        return;
    }
    stepSize = stepSize * stepSize;

    ngl::Vec3 storedPos = m_pos;
    m_pos += (m_pos - m_oldPos) * (1.0 - damping) + m_acceleration * stepSize;
    m_oldPos = storedPos;
    resetAcceleration();
}