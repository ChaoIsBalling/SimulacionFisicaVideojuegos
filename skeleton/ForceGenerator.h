#pragma once
#include"Particula.h"
#include"RigidSolid.h"
#include <list>
 class ForceGenerator
{
protected:
	Vector3 force;
public:
	ForceGenerator(){};
	~ForceGenerator(){};
	virtual void update(Particula* p) = 0;
	virtual void update(RigidSolid* s) = 0;
	//virtual void clearForce() = 0;
};

