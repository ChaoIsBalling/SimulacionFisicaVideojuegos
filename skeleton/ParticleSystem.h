#pragma once
#include<list>
#include "Particula.h"
#include <random>
#include"ParticleForceRegistry.h"
#include"GravityForceGenerator.h"
#include"WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
enum Mode{RAIN,MIST,WATERFALL,STATIC};

const int MAXPARTICULAS = 100000;

class ParticleSystem
{ private:
	list<Particula*> lista;
	list<ForceGenerator*>forceList;
	std::mt19937 _mt;
	Mode modo;
	Vector3 pos;
	Vector3 accel;
	Vector3 speed;
	GravityForceGenerator* g;
	WindForceGenerator* w;
	TornadoForceGenerator* t;
	ExplosionForceGenerator* e;
public:
	ParticleSystem(Vector3 P, Vector3 A, Vector3 S) :pos(P), accel(A), speed(S) {
		modo = STATIC;
		g = new GravityForceGenerator();
	  	w = new WindForceGenerator(Vector3(20,0,0),1000);
		t = new TornadoForceGenerator(100);
		e = new ExplosionForceGenerator(1000, Vector3(0,0,0),100000,10000);
	};
	ParticleForceRegistry reg = ParticleForceRegistry();

	void generateSpringDemo();
	void changeModes(int i);
	void clear();
	void kill();
	void generate();
	void setBlast();
	void update(double t);
};

