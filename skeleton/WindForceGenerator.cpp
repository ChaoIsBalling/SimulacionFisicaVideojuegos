#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator()
{
}

void WindForceGenerator::update(Particula* p)
{
	
		p->addForce(force);
}
