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
}
