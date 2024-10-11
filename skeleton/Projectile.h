#pragma once
#include "Particula.h"
class Projectile:public Particula
{

public:

	Projectile(Vector3 p, Vector3 v, Vector3 a):Particula(p,v,a,20.0,100.0){}
	bool integrate(double t, bool semi);
};

