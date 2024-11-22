#pragma once
#include <ctype.h>
#include <PxPhysicsAPI.h>
#include"RenderUtils.hpp"
#include"PxRigidDynamic.h"
#include"core.hpp"
#include "callbacks.hpp"

using namespace physx;

class RigidSolid
{private:
	PxTransform  pose;
	float life;
	PxRigidDynamic* solid = nullptr;
	PxShape* shape = nullptr;
	RenderItem* render = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

public:
	RigidSolid(PxTransform p,PxRigidDynamic* s, float l,PxPhysics* g,PxScene* gS) :pose(p),life(l),solid(s),gPhysics(g),gScene(gS) {
		
		solid = gPhysics->createRigidDynamic(pose);
		solid->setLinearVelocity({ 0,5,0 });
		solid->setAngularVelocity({ 0,0,0 });
		shape = CreateShape(PxBoxGeometry(5, 5, 5));
		solid->attachShape(*shape);
		render = new RenderItem(shape, solid, { 1,0,0,1 });
		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		gScene->addActor(*solid);

		//render = new RenderItem(solid,shape, pose, { 1,0,0,1 });
	
	
	};
	~RigidSolid();

};

