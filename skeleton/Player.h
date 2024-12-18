#pragma once
#include"RigidSolid.h"

class Player:public RigidSolid
{
public:
	Player(PxTransform p, Vector3 speed, float l, PxPhysics* g, PxScene* gS, Vector4 Color) :RigidSolid(p, speed, l, g, gS, Color,7,true,5) {};
	void Move(Vector3 dir);
	void Jump();
};

