#pragma once
#include"ForceGenerator.h"
class SpringForceGenerator:public ForceGenerator
{
private:
	double k;
	double restingLength;
	Particula* other;
public:
	SpringForceGenerator(double K, double r, Particula* p) :k(K),restingLength(r),other(p) {};
	void update(Particula* p) override;
	inline void setK(double K) { k = K; };
	~SpringForceGenerator() {};
};

