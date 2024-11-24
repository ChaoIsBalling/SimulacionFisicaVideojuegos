#include "SolidSystem.h"

void SolidSystem::generateSpringDemo()
{
}

void SolidSystem::changeModes(int i)
{
	if (i == 0)
		modo = RAIN;
	else if (i == 1)
		modo = MIST;
	else if (i == 2)
		modo = WATERFALL;
}

void SolidSystem::clear()
{
	while (!lista.empty())
	{
		reg.freeSolid(lista.front());
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

void SolidSystem::kill()
{
	if (lista.size() > MAXSOLID)
	{
		reg.freeSolid(lista.front());
		delete lista.front();
		lista.pop_front();
	}
}

void SolidSystem::generate()
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
		TornadoForceGenerator* t = new TornadoForceGenerator(1000);
		RigidSolid* aux = new RigidSolid(PxTransform(newPos), newSpeed, 100, gPhysics, gScene, color);
		lista.push_back(aux);

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
		RigidSolid* aux = new RigidSolid(PxTransform(newPos), newSpeed, 100, gPhysics, gScene, color);
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
		RigidSolid* aux = new RigidSolid(PxTransform(newPos), newSpeed, 100, gPhysics, gScene, color);
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
		RigidSolid* aux = new RigidSolid(PxTransform(newPos), Vector3(0, 0, 0),100, gPhysics,gScene,color);
		lista.push_back(aux);
	}
}

void SolidSystem::setBlast()
{
	for (auto a : lista)
	{
		ExplosionForceGenerator* e = new ExplosionForceGenerator(1000, Vector3(0, 0, 0), 100000, 10000);
		reg.RegisterParticle(a, e);
		forceList.push_back(e);
	}
}

void SolidSystem::AddK()
{
	for (auto a : springList)
	{
		a->setK(a->getK() + 1);
	}
}

void SolidSystem::update(double t)
{
	generate();
	reg.update();
	for (auto it = lista.begin(); it != lista.end();)
	{
		(*it)->integrate(t);
		if (!(*it)->GetAlive())
		{
			reg.freeSolid(*it);
			delete (*it);
			it = lista.erase(it);
		}
		else
			it++;
	}
	kill();
}
