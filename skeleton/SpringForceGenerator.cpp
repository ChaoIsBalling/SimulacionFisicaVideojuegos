#include "SpringForceGenerator.h"

void SpringForceGenerator::update(Particula* p)
{
	Vector3 relative_pos_vector = other->getPos() - p->getPos();

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - restingLength;
	force = relative_pos_vector * delta_x * k;
	p->addForce(force);
}

void SpringForceGenerator::update(RigidSolid* p)
{
	Vector3 relative_pos_vector = other->getPos() - p->getPos();

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - restingLength;
	force = relative_pos_vector * delta_x * k;
	p->addForce(force);
}
