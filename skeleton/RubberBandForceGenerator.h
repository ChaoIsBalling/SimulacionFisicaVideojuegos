#pragma once
#include"SpringForceGenerator.h"
class RubberBandForceGenerator:public SpringForceGenerator
{
public:
	RubberBandForceGenerator(double K, double r, Particula* p) : SpringForceGenerator(K, r, p) {
};
	void update(Particula* p) override;
};

