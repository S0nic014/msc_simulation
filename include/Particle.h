#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>

class Particle
{
private:
    ngl::Vec3 m_pos;
    ngl::Vec3 m_oldPos;
    ngl::Vec3 m_acceleration = ngl::Vec3(0.0f, 0.0f, 0.0f);
    ngl::Vec3 m_accumulatedNormal = ngl::Vec3(0.0f, 0.0f, 0.0f);
    bool m_isMovable = true;
    float m_mass = 1.0f;

public:
    Particle(ngl::Vec3 pos) : m_pos(pos), m_oldPos(pos) {}
    void setMovable(bool state) { m_isMovable = state; }
    ngl::Vec3 &position() { return m_pos; }
    ngl::Vec3 &normal() { return m_accumulatedNormal; }
    void resetAcceleration() { m_acceleration = ngl::Vec3(0.0f, 0.0f, 0.0f); }
    void resetNormal() { m_accumulatedNormal = ngl::Vec3(0.0f, 0.0f, 0.0f); }

    void drawSphere() const;
    void addForce(ngl::Vec3 force);
    void offsetPosition(const ngl::Vec3 offset);
    void addToNormal(ngl::Vec3 normal);
    void timeStep(const float damping, const float stepSize);
};

#endif