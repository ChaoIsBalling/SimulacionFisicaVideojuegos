#pragma once
#include <map>
#include"ForceGenerator.h"

class ParticleForceRegistry: public multimap<Particula*,ForceGenerator*>
{
private:

public:
	ParticleForceRegistry() {}
	void RegisterParticle(Particula* p, ForceGenerator* f) {
		insert(pair<Particula*, ForceGenerator*>(p, f));
     }
	void freeParticle(Particula* p)
	{
		for (auto itr = begin(); itr != end();)
		{
			if (itr->first == p)
			{
				itr=erase(itr);
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
				itr= erase(itr);
			}
			else {
				++itr;
			}
		}
	}
	void update()
	{
		for(auto itr=begin();itr!=end();++itr)
		{
			itr->second->update(itr->first);
		}
	}
	
};

