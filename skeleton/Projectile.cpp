#include "Projectile.h"

bool Projectile::integrate(double t, bool semi)
{
	if (!alive)
		return false;

	if (pose.p.y > 5)
		Particula::integrate(t, semi);
	else
	{
		DeregisterRenderItem(renderItem);
		alive = false;
	}
	
	cout << pose.p.y << endl;
}
