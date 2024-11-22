#pragma once
#include"core.hpp"
#include"SpringForceGenerator.h"
class AnchoredSpringFG:public SpringForceGenerator
{
private:
	RenderItem* render;
	
public:
	AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos);
	~AnchoredSpringFG();
};

