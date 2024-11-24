#pragma once
#include"ForceGenerator.h"
class SpringForceGenerator:public ForceGenerator
{
protected:
	double k;
	double restingLength;
protected:
	Particula* other;
public:
	SpringForceGenerator(double K, double r, Particula* p) :k(K),restingLength(r),other(p) {};
	void update(Particula* p) override;
	void update(RigidSolid* p) override;
	inline void setK(double K) { k = K; };
	inline double getK() { return k; }
	~SpringForceGenerator() {};
};

