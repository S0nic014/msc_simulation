#include "Cloth.h"
#include <fmt/format.h>
#include <GL/GL.h>

Cloth::Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight, ngl::Vec3 originPosition)
{
    // Move origin transform
    m_transform.setPosition(originPosition);

    // Generating particles grid and constraints between them
    m_width = width;
    m_height = height;
    m_numParticlesWidth = numParticlesWidth;
    m_numParticlesHeight = numParticlesHeight;

    // Total particles grid size: width * height
    m_particles.resize(numParticlesWidth * numParticlesHeight);

    // Creating grid of particles
    for (int x = 0; x < numParticlesWidth; x++)
    {
        for (int y = 0; y < numParticlesHeight; y++)
        {
            ngl::Vec3 position = {width * (x / (float)numParticlesWidth),
                                  -height * (y / (float)numParticlesHeight),
                                  0};
            position += m_transform.getPosition();
            m_particles[y * numParticlesWidth + x] = std::make_shared<Particle>(position);
        }
    }

    // Connecting immediate neighbour particles with constraints
    for (int x = 0; x < numParticlesWidth; x++)
    {
        for (int y = 0; y < numParticlesHeight; y++)
        {
            if (x < numParticlesWidth - 1)
            {
                createConstraint(getParticle(x, y), getParticle(x + 1, y));
            }
            if (y < numParticlesHeight - 1)
            {
                createConstraint(getParticle(x, y), getParticle(x, y + 1));
            }
            if (x < numParticlesWidth - 1 && y < numParticlesHeight - 1)
            {
                createConstraint(getParticle(x, y), getParticle(x + 1, y + 1));
                createConstraint(getParticle(x + 1, y), getParticle(x, y + 1));
            }
        }
    }

    // Connecting secondary neibours
    for (int x = 0; x < numParticlesWidth; x++)
    {
        for (int y = 0; y < numParticlesHeight; y++)
        {
            if (x < numParticlesWidth - 2)
            {
                createConstraint(getParticle(x, y), getParticle(x + 2, y));
            }
            if (y < numParticlesHeight - 2)
            {
                createConstraint(getParticle(x, y), getParticle(x, y + 2));
            }
            if (x < numParticlesWidth - 2 && y < numParticlesHeight - 2)
            {
                createConstraint(getParticle(x, y), getParticle(x + 2, y + 2));
                createConstraint(getParticle(x + 2, y), getParticle(x, y + 2));
            }
        }
    }

    // Pin three upper left and right particles by making not movable
    for (int i = 0; i < 3; i++)
    {
        getParticle(i, 0)->offsetPosition({0.5f, 0.0f, 0.0f});
        getParticle(i, 0)->setMovable(false);

        getParticle(numParticlesWidth - 1 - i, 0)->offsetPosition({-0.5f, 0.0f, 0.0f});
        getParticle(numParticlesWidth - 1 - i, 0)->setMovable(false);
    }
}

void Cloth::move(ngl::Vec3 position)
{
    m_transform.setPosition(position);
    for (auto p : m_particles)
    {
        p->offsetPosition(position, true);
    }
}

ngl::Vec3 Cloth::calculateTriangleNormal(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3)
{
    ngl::Vec3 v1 = p2->position() - p1->position();
    ngl::Vec3 v2 = p3->position() - p1->position();
    return v1.cross(v2);
}

void Cloth::drawTriangle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3)
{
    ngl::Vec3 p1Normal = p1->normal();
    ngl::Vec3 p2Normal = p2->normal();
    ngl::Vec3 p3Normal = p3->normal();
    p1Normal.normalize();
    p2Normal.normalize();
    p3Normal.normalize();

    float positions[9] = {p1->position()[0], p1->position()[1], p1->position()[2],
                          p2->position()[0], p2->position()[1], p2->position()[2],
                          p3->position()[0], p3->position()[1], p3->position()[2]};

    // TODO: Drawing triagle from particles
    unsigned int triBuffer;
    glGenBuffers(1, &triBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triBuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // glNormal3fv((GLfloat *)&(p1Normal));
    // glVertex3fv((GLfloat *)&(p1->position()));

    // glNormal3fv((GLfloat *)&(p2Normal));
    // glVertex3fv((GLfloat *)&(p2->position()));

    // glNormal3fv((GLfloat *)&(p3Normal));
    // glVertex3fv((GLfloat *)&(p3->position()));
}

void Cloth::drawShaded()
{
    // Reset normals
    for (auto p : m_particles)
    {
        p->resetNormal();
    }

    // Create smooth by adding up hard normals
    for (int x = 0; x < m_numParticlesWidth - 1; x++)
    {
        for (int y = 0; y < m_numParticlesHeight - 1; y++)
        {
            ngl::Vec3 normal = calculateTriangleNormal(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1));
            getParticle(x + 1, y)->addToNormal(normal);
            getParticle(x, y)->addToNormal(normal);
            getParticle(x, y + 1)->addToNormal(normal);

            normal = calculateTriangleNormal(getParticle(x + 1, y + 1), getParticle(x, y), getParticle(x, y + 1));
            getParticle(x + 1, y + 1)->addToNormal(normal);
            getParticle(x + 1, y)->addToNormal(normal);
            getParticle(x, y + 1)->addToNormal(normal);
        }
    }
    // TODO: Draw shaded mesh
    for (int x = 0; x < m_numParticlesWidth - 1; x++)
    {
        for (int y = 0; y < m_numParticlesHeight - 1; y++)
        {
            drawTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1));
            drawTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1));
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}

void Cloth::addForce(const ngl::Vec3 direction)
{
    for (auto p : m_particles)
    {
        p->addForce(direction);
    }
}

void Cloth::applyGravity()
{
    for (auto p : m_particles)
    {
        p->applyGravity(m_gravity);
    }
}

void Cloth::addWindForceToTringle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, std::shared_ptr<Particle> p3, const ngl::Vec3 direction)
{
    ngl::Vec3 normal = calculateTriangleNormal(p1, p2, p3);
    ngl::Vec3 d = normal;
    d.normalize();
    ngl::Vec3 force = normal * (d.dot(direction));
    p1->addForce(force);
    p2->addForce(force);
    p3->addForce(force);
}

void Cloth::windForce(const ngl::Vec3 direction)
{
    for (int x = 0; x < m_numParticlesWidth - 1; x++)
    {
        for (int y = 0; y < m_numParticlesHeight - 1; y++)
        {
            addWindForceToTringle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), direction);
            addWindForceToTringle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), direction);
        }
    }
}

void Cloth::sphereCollision(const ngl::Vec3 centerPoint, const float radius)
{
    for (auto p : m_particles)
    {
        ngl::Vec3 toCenter = p->position() - centerPoint;
        float distance = toCenter.length();
        if (toCenter.length() < radius) // Particle inside the sphere
        {
            toCenter.normalize();
            p->offsetPosition(toCenter * (radius - distance));
        }
    }
}

void Cloth::timeStep()
{
    for (int i = 0; i < m_constraintIterations; i++)
    {
        for (auto cnstr : m_constraints)
        {
            cnstr->satisfy();
        }
    }

    for (auto p : m_particles)
    {
        p->timeStep(m_damping, m_simulationStepSize);
    }
}