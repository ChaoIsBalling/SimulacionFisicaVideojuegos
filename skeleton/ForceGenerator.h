#pragma once
#include"Particula.h"
#include <list>
 class ForceGenerator
{
protected:
	Vector3 force;
public:
	ForceGenerator(){};
	~ForceGenerator(){};
	virtual void update(Particula* p) = 0;
	//virtual void clearForce() = 0;
};

