#pragma once
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include <vector>
#include "Constraint.h"
#include "Particle.h"

class Cloth
{
private:
    // Simulation
    float m_damping = 0.01f;
    float m_simulationStepSize = 0.5f;
    int m_constraintIterations = 20;
    float m_gravity = 0.01f;
    // Members
    std::vector<std::shared_ptr<Particle>> m_particles;
    std::vector<std::shared_ptr<Constraint>> m_constraints;
    // Cloth density/size
    float m_width;
    float m_height;
    int m_numParticlesHeight;
    int m_numParticlesWidth;
    ngl::Transformation m_transform;

    std::shared_ptr<Particle> getParticle(int x, int y) { return m_particles[y * m_numParticlesWidth + x]; }
    void createConstraint(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2) { m_constraints.push_back(std::make_shared<Constraint>(p1, p2)); }
    ngl::Vec3 calculateTriangleNormal(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3);
    void addWindForceToTringle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3, const ngl::Vec3 direction);
    void drawTriangle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3);

public:
    Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight, ngl::Vec3 originPosition = ngl::Vec3(0.0f, 0.0f, 0.0f));
    // Simulation
    std::vector<std::shared_ptr<Particle>> particles() const { return m_particles; }
    float damping() const { return m_damping; }
    void setDamping(const float value) { m_damping = value; }
    float stepSize() const { return m_simulationStepSize; }
    float stepSize2() const { return m_simulationStepSize * m_simulationStepSize; }
    void setStepSize(const float newSize) { m_simulationStepSize = newSize; }
    int constraintIterations() const { return m_constraintIterations; }
    void setConstraintIterations(const int value) { m_constraintIterations = value; }
    float gravity() const { return m_gravity; }
    void setGravity(float value) { m_gravity = value; }
    void doFrame() {}
    // Cloth size/density
    float width() const { return m_width; }
    float height() const { return m_height; }
    int numParticlesWidth() const { return m_numParticlesWidth; }
    int numParticlesHeight() const { return m_numParticlesHeight; }

    // Transform
    ngl::Transformation transform() const { return m_transform; }
    void move(ngl::Vec3 position);
    //Forces
    void addForce(const ngl::Vec3 direction);
    void applyGravity();
    void windForce(const ngl::Vec3 direction);
    void timeStep();
    void sphereCollision(const ngl::Vec3 centerPoint, const float radius);
    // Drawing
    void drawShaded();
};
