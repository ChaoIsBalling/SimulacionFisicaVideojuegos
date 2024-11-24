#pragma once
#include"ForceGenerator.h"
class GravityForceGenerator:public ForceGenerator
{
private:
public:
	GravityForceGenerator();
	void update(Particula* p)override;
	void update(RigidSolid* p)override;

};

