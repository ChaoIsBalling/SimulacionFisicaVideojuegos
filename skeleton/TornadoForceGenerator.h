#pragma once
#include "ForceGenerator.h"
class TornadoForceGenerator:public ForceGenerator
{
private:
	double radius;
	Vector3 pos;
public:
	TornadoForceGenerator( double r,Vector3 p ={0,0,0}) : radius(r),pos(p) {};
	void update(Particula* p)override;
	void update(RigidSolid* p)override;
};

