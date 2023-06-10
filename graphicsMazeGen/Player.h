#ifndef PLAYER_H
#define PLAYER_H

#include "EntityStats.h"
#include "Entity.h"

class Player : private Entity
{
public:
	Player()
	{
	}

	Player(unsigned int health, unsigned int mana)
	{
		stats = EntityStats();

		stats.SetHealth(health);
		stats.SetMana(mana);
	}

	EntityStats GetStats()
	{
		return stats;
	}

	void ApplyDamageBy(unsigned int value)
	{
		stats.SetHealth(stats.GetHealth() - value);
	}
};
#endif
