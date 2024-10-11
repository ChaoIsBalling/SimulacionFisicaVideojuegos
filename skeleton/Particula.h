#pragma once
#include"RenderUtils.hpp"
#include"core.hpp"
#include <iostream>
using namespace physx;
using namespace std;
class Particula
{
protected:
	Vector3 vel;
	Vector3 accel;
	double lifeTime;
	bool alive = true;
	Vector3 posIni;
	float maxBound=100;
	double damping = 0.98;
	physx::PxTransform pose;
	RenderItem* renderItem;
public:
	Particula(Vector3 p, Vector3 v,Vector3 a, double l, float b) :vel(v), pose(p),accel(a),lifeTime(l),posIni(p),maxBound(b)
	{ 
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &pose, { 1.0, 0.0, 0.0, 1.0 });
	};
	~Particula() { DeregisterRenderItem(renderItem); };
	void integrate(double t,bool semi);
	bool Alive(){ return alive; }
};

