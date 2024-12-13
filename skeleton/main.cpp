#include <ctype.h>

#include <PxPhysicsAPI.h>
#include <map>
#include <vector>
#include "Vector3D.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include"Projectile.h"
#include "ParticleSystem.h"
#include "SolidSystem.h"
#include "RigidSolid.h"
#include"Player.h"
#include <iostream>
#include"System.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;


PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* sphereItem = nullptr;
PxTransform* spheretransform = nullptr;
System* sistema = nullptr;
vector<System*> sistemas;
vector <Projectile*> lista;
RigidSolid* solid = nullptr;
Player* player = nullptr;
//Particula* p = nullptr;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	//Vector3D spher = Vector3D(1.0, 5.0, 6.0);
	//Vector3D* sphere = new Vector3D(1.0, 5.0, 6.0);
	//Vector3D a = spher*2.0f;
	//std::cout << a.getX();

	//spheretransform = new PxTransform(Vector3(0, 0, 0));
	//sphereItem = new RenderItem(CreateShape(PxSphereGeometry(10)), spheretransform ,{1.0, 0.0, 0.0, 1.0});
	
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(1000, 0.1, 1000));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);

	player = new Player(PxTransform({ 20,20,0 }),Vector3(0,0,0), 100000, gPhysics, gScene, {0,1,0,1});

	RenderItem* item;
	item = new RenderItem(shape, Suelo, { 0,0.0,0,1 });

	//p = new Particula(Vector3(0,0,0),Vector3(2,0,0),Vector3(0,0,0),100,100);
	sistema = new ParticleSystem(Vector3(0,500,0),Vector3(0,-9.8,0),Vector3(0,10,0));
	sistema->changeModes(0);
	System* myst = new ParticleSystem(Vector3(0, 500, 0), Vector3(0, -9.8, 0), Vector3(0, 10, 0));
	myst->changeModes(1);
   System*  bounce = new ParticleSystem(Vector3(-200, 0, 0), Vector3(0, -9.8, 0), Vector3(0, 10, 0));
	 bounce->generateSpringDemo();
	 System* bounce2 = new ParticleSystem(Vector3(300, 0, 0), Vector3(0, -9.8, 0), Vector3(0, 10, 0));
	 bounce2->generateSpringDemo();
	 System* bounce3 = new SolidSystem(Vector3(50, 0, 220), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 bounce3->changeModes(4);
	 bounce3->generateSpringDemo();
	 System* bounce4 = new SolidSystem(Vector3(50, 0, -250), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 bounce4->changeModes(4);
	 bounce4->generateSpringDemo();

	 System* stuff = new SolidSystem(Vector3(200, 00, 200), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 stuff->changeModes(3);
	 System* stuff2 = new SolidSystem(Vector3(-150, 00, 200), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 stuff2->changeModes(3);
	 System* stuff3 = new SolidSystem(Vector3(200, 00, -200), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 stuff3->changeModes(3);
	 System* stuff4 = new SolidSystem(Vector3(-150, 00, -200), Vector3(0, -9.8, 0), Vector3(0, 10, 0), gPhysics, gScene);
	 stuff4->changeModes(3);
	 sistemas.push_back(stuff3);
	 sistemas.push_back(stuff4);
	 sistemas.push_back(stuff2);
	 sistemas.push_back(stuff);
	 sistemas.push_back(sistema);
	 sistemas.push_back(myst);
	 sistemas.push_back(bounce);
	 sistemas.push_back(bounce2);
	 sistemas.push_back(bounce3);
	 sistemas.push_back(bounce4);
   //sistema->generateSpringDemo();
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	for (int i = 0; i < lista.size(); i++)
	{
		lista[i]->integrate(t, false);
		if (!lista[i]->Alive())
		{
			lista.erase(lista.begin() + i);
		}
	}
//	p->integrate(t, true);
	for (auto a : sistemas)
	{
		a->update(t);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	//DeregisterRenderItem(sphereItem);
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'Z':
		lista.push_back(new Projectile(Vector3(30, 35, 40), Vector3(0.0, 20.0, -5.0), Vector3(0, -9.8, 0)));
		break;
	case'E':
		sistema->setBlast();
		break;
	case'K':
		sistema->AddK();
			break;
	case'F':
		player->Move({-30,0,0});
	break;
	case 'H':
		player->Move({ 30,0,0 });
	break;
	case'T':
		player->Move({ 0,0,-30 });
		break;
	case'G':
		player->Move({ 0,0,30 });
		break;
	//case 'B': break;
	//case ' ':	break;
	case '0':
	{
		sistema->changeModes(0);
		sistema->clear();
		break;
	}
	case'1':
	{
		sistema->changeModes(1);
		sistema->clear();
		break;
	}
	case'2':
	{
		sistema->changeModes(2);
		sistema->clear();
		break;
	}
	case '3':
		sistema->clear();
		
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}