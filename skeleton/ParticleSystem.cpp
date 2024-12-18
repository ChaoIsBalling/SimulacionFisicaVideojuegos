#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
	clear();
}

void ParticleSystem::generateSpringDemo()
{GravityForceGenerator* g = new GravityForceGenerator();
	//Particula* p1 = new Particula({-10.0,10.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},100,100,false);
	//Particula* p2= new Particula({10.0,10.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},100,100,false);
	//p2->setMass(2.0);
	//RubberBandForceGenerator* f1 = new RubberBandForceGenerator(1, 5, p2);
	//reg.RegisterParticle(p1, f1);
	//reg.RegisterParticle(p1, g);
	//RubberBandForceGenerator* f2 = new RubberBandForceGenerator(1, 5, p1);
	//reg.RegisterParticle(p2, f2);
	////reg.RegisterParticle(p2, g);
	//lista.push_back(p1);
	//lista.push_back(p2);
	//forceList.push_back(f1);
	//forceList.push_back(f2);
	//forceList.push_back(g);
	//springList.push_back(f1);
	//springList.push_back(f2);

	//ANCHORED

	//Particula* p3 = new Particula({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 100, 100, false);	
	//reg.RegisterParticle(p3, g);
	//AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0,20.0,0.0 });
	//reg.RegisterParticle(p3,f3);
	//lista.push_back(p3);
	//forceList.push_back(f3);
	//springList.push_back(f3);

 //BUOYANCY

Vector3 newpos = pos;
newpos.y += 20;
Particula* p4 = new Particula(newpos, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 10000, 10000, false, {1,1,0,1},5,5);
	BuoyancyForceGenerator* f4= new BuoyancyForceGenerator(10,1 ,1000,pos);
	forceList.push_back(f4);
	forceList.push_back(g);
	lista.push_back(p4);
	reg.RegisterParticle(p4, f4);
	reg.RegisterParticle(p4, g);
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
		newPos.x += uniform_real_distribution<float>(-100, 200)(_mt);
		newPos.y += uniform_real_distribution<float>(0, 10)(_mt);
		newPos.z += uniform_real_distribution<float>(-100, 200)(_mt);
		newSpeed.x += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.y -= uniform_real_distribution<float>(50, 100)(_mt);
		newSpeed.z += uniform_real_distribution<float>(0, 1)(_mt);
		float f = uniform_real_distribution<float>(0, 1)(_mt);
		float mass = uniform_real_distribution<float>(1, 20)(_mt);
		Vector4 color = { 0,0.5,1,0.1 };
		Particula* aux = new Particula(newPos, newSpeed, {0,0,0}, 10, 1000, false, color,f,mass);

		GravityForceGenerator* g = new GravityForceGenerator();
		reg.RegisterParticle(aux, g);
		lista.push_back(aux);
		forceList.push_back(g);

	}
	else if (modo == MIST)
	{
		newPos.y = 450;
		newPos.x += uniform_real_distribution<float>(0, 100)(_mt);
		newPos.y += uniform_real_distribution<float>(0, 100)(_mt);
		newPos.z += uniform_real_distribution<float>(0, 100)(_mt);
		newSpeed.y = 0;
		newSpeed.x += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.y += uniform_real_distribution<float>(0, 1)(_mt);
		newSpeed.z += uniform_real_distribution<float>(0, 1)(_mt);
		float f = uniform_real_distribution<float>(0, 0.3)(_mt);
		Vector4 color = { 1,1,1,0.7 };
		WindForceGenerator* w = new WindForceGenerator(Vector3(2, 0, 0), 1000);
		
		Particula* aux = new Particula(newPos, newSpeed, Vector3(0, 0, 0), 10, 1000,false, color,f);
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
		Particula* aux = new Particula(newPos, newSpeed, accel, 10, 100, false, color,f);
		TornadoForceGenerator* t = new TornadoForceGenerator(100);
		reg.RegisterParticle(aux, t);
		forceList.push_back(t);
		lista.push_back(aux);
	}
	else if (modo==STATIC) {
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

void ParticleSystem::AddK()
{
	for (auto a : springList)
	{
		a->setK(a->getK() + 1);
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
