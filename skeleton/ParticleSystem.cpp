#include "ParticleSystem.h"

void ParticleSystem::kill()
{
	if (lista.size() > maxParticula)
	{
		delete lista.front();
		lista.pop_front();
}
}

void ParticleSystem::generate()
{
	Vector3 newPos = pos;
	//newPos+=u(_mt)*
	lista.push_back(new Particula(pos, speed, accel,10,100));
}

void ParticleSystem::update(double t)
{
	generate();
	for (auto it =lista.begin(); it!=lista.end();)
	{
		(*it)->integrate(t, true);
		if (!(*it)->Alive())
		{
			delete (*it);
			it= lista.erase(it);
		}
		else
		it++;
	}
	kill();
}
