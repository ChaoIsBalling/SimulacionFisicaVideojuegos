#pragma once
#include <map>
#include"ForceGenerator.h"

class SolidForceRegistry : public multimap<RigidSolid*, ForceGenerator*>
{
private:

public:
	SolidForceRegistry() {}
	void RegisterParticle(RigidSolid* p, ForceGenerator* f) {
		insert(pair<RigidSolid*, ForceGenerator*>(p, f));
	}
	void freeSolid(RigidSolid* p)
	{
		for (auto itr = begin(); itr != end();)
		{
			if (itr->first == p)
			{
				itr = erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}
	void freeForce(ForceGenerator* f)
	{
		for (auto itr = begin(); itr != end();)
		{
			if (itr->second == f)
			{
				itr = erase(itr);
			}
			else {
				++itr;
			}
		}
	}
	void update()
	{
		for (auto itr = begin(); itr != end(); ++itr)
		{
			itr->second->update(itr->first);
		}
	}

};

