#pragma once
#include"System.h"
#include<list>
#include "Particula.h"
#include <random>
#include"ParticleForceRegistry.h"
#include"GravityForceGenerator.h"
#include"WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include"AnchoredSpringFG.h"
#include"RubberBandForceGenerator.h"
#include"BuoyancyForceGenerator.h"
const int MAXPARTICULAS = 10000;

class ParticleSystem: public System
{ private:
	list<Particula*> lista;
	list<ForceGenerator*>forceList;
	list<SpringForceGenerator*> springList;
	std::mt19937 _mt;
	Mode modo;
	Vector3 pos;
	Vector3 accel;
	Vector3 speed;
public:
	ParticleSystem(Vector3 P, Vector3 A, Vector3 S) :pos(P), accel(A), speed(S) {
		modo = ELSE;
	};
	~ParticleSystem();
	ParticleForceRegistry reg = ParticleForceRegistry();

	void generateSpringDemo()override;
	void changeModes(int i)override;
	void clear()override;
	void kill() override;
	void generate() override;
	void setBlast()override;
	void AddK() override;
	void update(double t)override;
};

