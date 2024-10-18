#include "ParticleSystem.h"

void ParticleSystem::changeModes(int i)
{
	if (i == 0)
		modo = RAIN;
	else if (i == 1)
		modo = MIST;
	else if (i == 2)
		modo = WATERFALL;
}

void ParticleSystem::clear()
{
	while (!lista.empty())
	{
		delete lista.front();
		lista.pop_front();
	}
}

void ParticleSystem::kill()
{
	if (lista.size() > MAXPARTICULAS)
	{
		delete lista.front();
		lista.pop_front();
}
}

void ParticleSystem::generate()
{
	Vector3 newPos;
	newPos = pos;
	Vector3 newSpeed;
	newSpeed = speed;
	if (modo == RAIN)
	{
		newPos.x += uniform_real_distribution<float>(0, 50)(_mt);
		newPos.y = 50;
		newPos.y += uniform_real_distribution<float>(0, 50)(_mt);
		newPos.z += uniform_real_distribution<float>(0, 50)(_mt);
		newSpeed.x += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.y -= uniform_real_distribution<float>(50, 100)(_mt);
		newSpeed.z += uniform_real_distribution<float>(0, 1)(_mt);
		float f = uniform_real_distribution<float>(0, 1)(_mt);
		Vector4 color = { 0,0,1,1 };
		lista.push_back(new Particula(newPos, newSpeed, accel, 10, 1000,f,color));
	}
	else if (modo == MIST)
	{
		newPos.y = 20;
		newPos.x += uniform_real_distribution<float>(0, 50)(_mt);
		newPos.y += uniform_real_distribution<float>(0, 50)(_mt);
		newPos.z += uniform_real_distribution<float>(0, 50)(_mt);
		newSpeed.y = 0;
		newSpeed.x += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.y += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.z += uniform_real_distribution<float>(0, 1)(_mt);
		float f = uniform_real_distribution<float>(0, 1)(_mt);
		Vector4 color = { 1,1,1,0.7 };
		lista.push_back(new Particula(newPos, newSpeed, Vector3(0,0,0), 10, 1000,f,color));
	}
	else if (modo == WATERFALL)
	{
		newPos.x += normal_distribution<float>(0, 2)(_mt);
		newPos.y = 100;
		newPos.y += normal_distribution<float>(0, 2)(_mt);
		newPos.z += normal_distribution<float>(0, 2)(_mt);
		newSpeed.x += normal_distribution<float>(0, 1)(_mt);
		newSpeed.y -= normal_distribution<float>(50, 100)(_mt);
		newSpeed.z += normal_distribution<float>(0, 1)(_mt);
		float f = uniform_real_distribution<float>(1, 2)(_mt);
		Vector4 color = { 0,0,1,1 };
		lista.push_back(new Particula(newPos, newSpeed, accel, 10, 100, f, color));
	}
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