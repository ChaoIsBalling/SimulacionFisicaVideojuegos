#pragma once
#include"ForceGenerator.h"
#include <cmath>
class ExplosionForceGenerator:public ForceGenerator
{
private:
	double radius;
	Vector3 pos;
	double K;
	float duration;
	float timePassed=0;
public:
	ExplosionForceGenerator(double r, Vector3 p,double k,float d) :radius(r),pos(p),K(k),duration(d){};
	void update(Particula* p)override;
};

