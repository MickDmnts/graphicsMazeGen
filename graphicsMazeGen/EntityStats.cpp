#include "EntityStats.h"

EntityStats::EntityStats()
{
	health = 0;
	mana = 0;
};

EntityStats::EntityStats(unsigned int health, unsigned int mana)
{
	if (health > 100) health = 100;
	if (mana > 100) mana = 100;

	EntityStats::health = health;
	EntityStats::mana = mana;
}

unsigned int EntityStats::GetHealth()
{
	return health;
}

unsigned int EntityStats::GetMana()
{
	return mana;
}

void EntityStats::SetHealth(unsigned int value)
{
	health = value;
}

void EntityStats::SetMana(unsigned int value)
{
	mana = value;
}