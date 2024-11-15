#pragma once
#include"core.hpp"
#include"ForceGenerator.h"
class BuoyancyForceGenerator:public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float v, float d);

	void update(Particula* p)override;
	
	~BuoyancyForceGenerator();

protected:
	float height;
	float volume;
	float liquidDensity;
	float gravity = 9.8;

	Particula* liquidParticle;
};

