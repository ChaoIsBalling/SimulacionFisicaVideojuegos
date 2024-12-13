#pragma once
#pragma once
#include"System.h"
#include<list>
#include "RigidSolid.h"
#include <random>
#include"SolidForceRegistry.h"
#include"GravityForceGenerator.h"
#include"WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include"AnchoredSpringFG.h"
#include"RubberBandForceGenerator.h"
#include"BuoyancyForceGenerator.h"
const int MAXSOLID = 20;
class SolidSystem:public System
{
private:
	list<RigidSolid*> lista;
	list<ForceGenerator*>forceList;
	list<SpringForceGenerator*> springList;
	std::mt19937 _mt;
	Mode modo;
	PxPhysics* gPhysics;
	PxScene* gScene;
	Vector3 pos;
	Vector3 accel;
	Vector3 speed;
public:
	SolidSystem(Vector3 P, Vector3 A, Vector3 S, PxPhysics* g, PxScene* gS) :pos(P), accel(A), speed(S),gPhysics(g),gScene(gS) {
		modo = ELSE;
	};
	SolidForceRegistry reg = SolidForceRegistry();
	void generateSpringDemo()override;
	void changeModes(int i)override;
	void clear()override;
	void kill() override;
	void generate() override;
	void setBlast()override;
	void AddK() override;
	void update(double t)override;
};

