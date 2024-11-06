#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator()
{
	force = { 0,-9.8,0 };
}

void GravityForceGenerator::update(Particula* p)
{
	p->addForce(force);
}