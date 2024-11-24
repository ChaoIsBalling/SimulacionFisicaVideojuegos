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
	Vector3 posIni;
	Vector3 accForce = { 0,-9.8,0 };
	physx::PxTransform pose;
	RenderItem* renderItem;
	double lifeTime;
    double damping = 0.98;
	bool alive = true;
	bool cube;
	float maxBound=100;
	float mass;

public:
	Particula(Vector3 p, Vector3 v, Vector3 a, double l, float b, bool CUBE = false, Vector4 color = { 0.0, 1.0, 0.0, 1.0 },float size = 1.0f ,
		float m=1) :vel(v), pose(p),accel(a),lifeTime(l),posIni(p),maxBound(b), mass(m),cube(CUBE)
	{ 
		if(!cube)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
		else
			renderItem = new RenderItem(CreateShape(PxBoxGeometry(size,size,size)), &pose, color);
	};
	void setMass(float m) { mass = m; }
	~Particula() { DeregisterRenderItem(renderItem); };
	void integrate(double t,bool semi);
	void addForce(Vector3 f);
	void clearForce();
	Vector3 getVel() { return vel; }
	Vector3 getPos() { return pose.p;}
	bool Alive() { return alive;};
};

