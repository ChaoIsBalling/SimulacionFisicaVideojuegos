#pragma once
#include "Particula.h"
class Projectile:public Particula
{
protected:
	bool alive=true;

public:

	Projectile(Vector3 p, Vector3 v, Vector3 a):Particula(p,v,a){}
	bool integrate(double t, bool semi);
	bool Alive()
	{
		return alive;
	}
};

