#include "WindForceGenerator.h"
void WindForceGenerator::update(Particula* p)
{
	float k1;
	k1 = 0.5;
	force = k1 * (vel - p->getVel());
	if((pos-p->getPos()).magnitudeSquared()<radius*radius)
		p->addForce(force);
}

void WindForceGenerator::update(RigidSolid* p)
{
	float k1;
	k1 = 0.5;
	force = k1 * (vel - p->getVel());
	if ((pos - p->getPos()).magnitudeSquared() < radius * radius)
		p->addForce(force);
}
