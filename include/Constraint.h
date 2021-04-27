#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <memory>
#include "Particle.h"

class Constraint
{
private:
    float m_restDistance;

public:
    Constraint(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
    std::shared_ptr<Particle> p1;
    std::shared_ptr<Particle> p2;
    void satisfy();
};

#endif