#include <ngl/Vec3.h>
#include "Constraint.h"

Constraint::Constraint(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
    this->p1 = p1;
    this->p2 = p2;
    m_restDistance = (p1->position() - p2->position()).length();
}

void Constraint::satisfy()
{
    ngl::Vec3 p1Top2 = p2->position() - p1->position();
    float currentDistance = p1Top2.length();
    ngl::Vec3 correctiveVec = p1Top2 * (1 - m_restDistance / currentDistance);
    ngl::Vec3 correctiveHalf = correctiveVec * 0.5f;
    p1->offsetPosition(correctiveHalf);
    p2->offsetPosition(-correctiveHalf);
}