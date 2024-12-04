#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float v, float d,Vector3 pos):height(h),volume(v),liquidDensity(d)
{
	liquidParticle = new Particula(pos, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 100, 100, true, {0,0,1,1},10);
}

void BuoyancyForceGenerator::update(Particula* p)
{
	float h = p->getPos().y;
	float h0 = liquidParticle->getPos().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > height * 0.5)
		immersed = 0.0;
	else if (h0 - h > height * 0.5)
		immersed = 1.0;
	else
		immersed = (h0 - h) / height + 0.5;
	f.y = liquidDensity * volume * immersed * gravity;
	p->addForce(f);
}

void BuoyancyForceGenerator::update(RigidSolid* p)
{
	float h = p->getPos().y;
	float h0 = liquidParticle->getPos().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > height * 0.5)
		immersed = 0.0;
	else if (h0 - h > height * 0.5)
		immersed = 1.0;
	else
		immersed = (h0 - h) / height + 0.5;
	f.y = liquidDensity * volume * immersed * gravity;
	p->addForce(f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
}
