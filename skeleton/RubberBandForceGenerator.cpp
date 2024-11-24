#include "RubberBandForceGenerator.h"

void RubberBandForceGenerator::update(Particula* p)
{
	//cout << (p->getPos() - other->getPos()).magnitude()<<endl;
	if (restingLength < (p->getPos()-other->getPos()).magnitude())
	{
		SpringForceGenerator::update(p);
	}
}
