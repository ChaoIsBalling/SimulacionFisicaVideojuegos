#pragma once
#include<list>
#include "Particula.h"
class ParticleSystem
{ private:
	list<Particula*> lista;
	
	int maxParticula;
	Vector3 pos;
	Vector3 accel;
	Vector3 speed;
	
public:
	ParticleSystem(Vector3 P, Vector3 A, Vector3 S, int max) :pos(P), accel(A), speed(S), maxParticula(max) {
	
		for (int i = 0; i < maxParticula; i++)
		{
			generate();
	}
	};
	void kill();
	void generate();
	void update(double t);
};

