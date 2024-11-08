#include "TornadoForceGenerator.h"

void TornadoForceGenerator::update(Particula* p)
{
	Vector3 vel;
	float k1,K;
	k1 = 0.5;
	K = 1;
	vel = K * Vector3(-(p->getPos().z - pos.z), 50-(p->getPos().y-pos.y), p->getPos().x - pos.x);
	force = k1 * (vel - p->getVel());
	if ((pos - p->getPos()).magnitudeSquared() < radius * radius)
		p->addForce(force);
}
