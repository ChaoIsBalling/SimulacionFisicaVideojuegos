#include "Particula.h"
void Particula::integrate(double t, bool semi)
{
	if (!semi)
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
