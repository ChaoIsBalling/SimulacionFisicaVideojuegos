#pragma once
#include<list>
#include "Particula.h"
#include <random>
enum Mode{RAIN,MIST,WATERFALL};

const int MAXPARTICULAS = 100000;

class ParticleSystem
{ private:
	list<Particula*> lista;
	std::mt19937 _mt;
	Mode modo;
	Vector3 pos;
	Vector3 accel;
	Vector3 speed;
	
public:
	ParticleSystem(Vector3 P, Vector3 A, Vector3 S) :pos(P), accel(A), speed(S) {
		modo = RAIN;
	};
	void changeModes(int i);
	void clear();
	void kill();
	void generate();
	void update(double t);
};

