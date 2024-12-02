#include "Player.h"

void Player::Move(float i)
{
	solid->setLinearVelocity({ i,0,0 });
}
