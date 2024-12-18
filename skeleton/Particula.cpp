#include "Particula.h"
void Particula::integrate(double t, bool semi)
{
	accel = accForce / mass;
	if (semi)
	{
		pose.p += vel * t;
		vel += accel * t;
		vel = vel * pow(damping, t);
	}
	else
	{
		vel += accel * t;
		vel = vel * pow(damping, t);
		pose.p += vel * t;
	}
	clearForce();
	lifeTime -= t;
	if (lifeTime<0||pose.p.x > posIni.x + maxBound || 
		pose.p.x < posIni.x - maxBound || 
		pose.p.y> posIni.y + maxBound || 
		pose.p.y < posIni.y - maxBound||
		pose.p.z> posIni.z + maxBound || 
		pose.p.z < posIni.z - maxBound)
	{
		alive = false;
	}
}

void Particula::addForce(Vector3 f)
{
	accForce += f;
}

void Particula::clearForce()
{
	accForce *= 0;
}
