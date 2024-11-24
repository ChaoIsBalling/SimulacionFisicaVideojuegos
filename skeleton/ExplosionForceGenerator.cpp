#include "ExplosionForceGenerator.h"

void ExplosionForceGenerator::update(Particula* p)
{
	double r = (pos - p->getPos()).magnitudeSquared();
	if ((pos - p->getPos()).magnitudeSquared() < radius)
	{
		force = K / pow(r, 2) * (p->getPos()-pos) * exp(-timePassed / duration);
		p->addForce(force);
	}
	timePassed++;
}

void ExplosionForceGenerator::update(RigidSolid* p)
{
	double r = (pos - p->getPos()).magnitudeSquared();
	if ((pos - p->getPos()).magnitudeSquared() < radius)
	{
		force = K / pow(r, 2) * (p->getPos() - pos) * exp(-timePassed / duration);
		p->addForce(force);
	}
	timePassed++;
}
