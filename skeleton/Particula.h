#pragma once
#include"RenderUtils.hpp"
#include"core.hpp"
using namespace physx;
class Particula
{
private:
	Vector3 vel;
	Vector3 accel = {1.0,0,0};
	double damping = 0.98;
	physx::PxTransform pose;
	RenderItem* renderItem;
public:
	Particula(Vector3 p, Vector3 v) :vel(v), pose(p)
	{ 
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
	};
	~Particula() { DeregisterRenderItem(renderItem); };
	void integrate(double t,bool semi);
};

