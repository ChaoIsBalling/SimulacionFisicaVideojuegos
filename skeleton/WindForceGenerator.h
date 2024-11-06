#pragma once
#include"ForceGenerator.h"
class WindForceGenerator:public ForceGenerator
{
private:
public:
	WindForceGenerator();
	void update(Particula* p)override;

};

