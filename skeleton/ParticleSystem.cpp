#include "ParticleSystem.h"

void ParticleSystem::generateSpringDemo()
{
	Particula* p1 = new Particula({-10.0,10.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},100,100,2);
	Particula* p2= new Particula({10.0,10.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},100,100,2);
	p2->setMass(2.0);
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	reg.RegisterParticle(p1, f1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	reg.RegisterParticle(p2, f2);
	lista.push_back(p1);
	lista.push_back(p2);
	forceList.push_back(f1);
	forceList.push_back(f2);
	Particula* p3 = new Particula({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 100, 100, 2);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0,20.0,0.0 });
	reg.RegisterParticle(p3,f3);
	lista.push_back(p3);
	forceList.push_back(f3);

}

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
		reg.freeParticle(lista.front());
		delete lista.front();
		lista.pop_front();
	}
	while (!forceList.empty())
	{
		reg.freeForce(forceList.front());
		delete forceList.front();
		forceList.pop_front();
	}
}

void ParticleSystem::kill()
{
	if (lista.size() > MAXPARTICULAS)
	{
		reg.freeParticle(lista.front());
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
		Particula* aux = new Particula(newPos, newSpeed, {0,0,0}, 10, 1000, f, color);

		GravityForceGenerator* g = new GravityForceGenerator();
		reg.RegisterParticle(aux, g);
		lista.push_back(aux);
		forceList.push_back(g);

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
		WindForceGenerator* w = new WindForceGenerator(Vector3(20, 0, 0), 1000);
		
		Particula* aux = new Particula(newPos, newSpeed, Vector3(0, 0, 0), 10, 1000, f, color);
		reg.RegisterParticle(aux, w);
		lista.push_back(aux);
		forceList.push_back(w);
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
		Particula* aux = new Particula(newPos, newSpeed, accel, 10, 100, f, color);
		TornadoForceGenerator* t = new TornadoForceGenerator(100);
		reg.RegisterParticle(aux, t);
		forceList.push_back(t);
		lista.push_back(aux);
	}
	else {
		newPos = Vector3(0, 0, 0);
		newPos.x += normal_distribution<float>(0, 2)(_mt);
		newPos.y += normal_distribution<float>(0, 2)(_mt);
		newPos.z += normal_distribution<float>(0, 2)(_mt);
		float f = uniform_real_distribution<float>(1, 2)(_mt);
		Vector4 color = { 0,0,1,1 };
		Particula* aux = new Particula(newPos, Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 100, f, color);
		lista.push_back(aux);
	}
}

void ParticleSystem::setBlast()
{
	for (auto a:lista)
	{
		ExplosionForceGenerator* e = new ExplosionForceGenerator(1000, Vector3(0, 0, 0), 100000, 10000);
		reg.RegisterParticle(a, e);
		forceList.push_back(e);
	}
}

void ParticleSystem::update(double t)
{
	generate();
	reg.update();
	for (auto it =lista.begin(); it!=lista.end();)
	{
		(*it)->integrate(t, true);
		if (!(*it)->Alive())
		{
			reg.freeParticle(*it);
			delete (*it);
			it= lista.erase(it);
		}
		else
		it++;
	}
	kill();
}
