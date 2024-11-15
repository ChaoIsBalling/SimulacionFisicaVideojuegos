#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos):SpringForceGenerator(k, resting, nullptr)
{
	other = new Particula(anchor_pos, { 0,0,0 }, { 0,0,0 }, 100,1000);
}
AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other;
}
