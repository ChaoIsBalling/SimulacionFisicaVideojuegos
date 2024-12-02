#include "Player.h"

void Player::Move(Vector3 dir)
{
	solid->setLinearVelocity(dir);
}

void Player::Jump()
{
	solid->addForce({0,100*solid->getMass(),0});
}
