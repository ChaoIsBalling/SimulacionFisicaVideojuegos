#pragma once
#include"core.hpp"
#include"ForceGenerator.h"
class BuoyancyForceGenerator:public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float v, float d,Vector3 pos);

	void update(Particula* p)override;
	void update(RigidSolid* p)override;
	
	~BuoyancyForceGenerator();

protected:
	float height;
	float volume;
	float liquidDensity;
	float gravity = 9.8;

	Particula* liquidParticle;
};

