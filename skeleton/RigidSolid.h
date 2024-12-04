#pragma once
#include <ctype.h>
#include <PxPhysicsAPI.h>
#include"RenderUtils.hpp"
#include"PxRigidDynamic.h"
#include"core.hpp"
#include "callbacks.hpp"

using namespace physx;

class RigidSolid
{
protected:
	PxTransform  pose;
	float life;
	bool alive = true;
	PxRigidDynamic* solid = nullptr;
	PxShape* shape = nullptr;
	RenderItem* render = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

public:
	RigidSolid(PxTransform p, Vector3 speed, float l, PxPhysics* g, PxScene* gS, Vector4 Color) :pose(p), life(l), gPhysics(g), gScene(gS) {

		solid = gPhysics->createRigidDynamic(pose);
		solid->setLinearVelocity({ 0,5,0 });
		solid->setAngularVelocity({ 0,0,0 });
		shape = CreateShape(PxSphereGeometry(5));
		solid->attachShape(*shape);
		render = new RenderItem(shape, solid, Color);
		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		gScene->addActor(*solid);
		solid->setLinearVelocity(speed);

		//render = new RenderItem(solid,shape, pose, { 1,0,0,1 });

	};
	void setMass(float m) { solid->setMass(m); }
	bool GetAlive() { return alive; }
	void  addForce(Vector3 force);
	void clearForce();
	Vector3 getVel() { return solid->getLinearVelocity(); }
	Vector3 getPos() { return solid->getGlobalPose().p; }
	void integrate(double t);
	~RigidSolid();
};

