#include "RigidSolid.h"

void RigidSolid::addForce(Vector3 force)
{
	solid->addForce(force);
}

void RigidSolid::clearForce()
{
	solid->clearForce();
}

void RigidSolid::integrate(double t)
{
	life -= t;
	if (life < 0)
	{
		alive = false;
	}
}

RigidSolid::~RigidSolid()
{
	DeregisterRenderItem(render);
}
