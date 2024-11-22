#include "RigidSolid.h"

RigidSolid::~RigidSolid()
{
	DeregisterRenderItem(render);
}
