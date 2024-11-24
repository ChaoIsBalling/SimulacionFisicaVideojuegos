#pragma once
#include"ForceGenerator.h"
class WindForceGenerator:public ForceGenerator
{
private:
	Vector3 vel;
	Vector3 pos;
	double radius;
public:
	WindForceGenerator(Vector3 v,double r,Vector3 p ={0,0,0}) :vel(v), radius(r),pos(p) {};
	void update(Particula* p)override;
	void update(RigidSolid* p)override;

};

