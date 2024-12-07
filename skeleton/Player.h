#pragma once
#include"RigidSolid.h"

class Player:public RigidSolid
{
public:
	Player(PxTransform p, Vector3 speed, float l, PxPhysics* g, PxScene* gS, Vector4 Color) :RigidSolid(p, speed, l, g, gS, Color,5,true) {};
	void Move(Vector3 dir);
	void Jump();
};

