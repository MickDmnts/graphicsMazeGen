#include "EntityStats.h"

/// <summary>
/// Creates an instance of EntityStats with 0 mana and health.
/// </summary>
EntityStats::EntityStats()
{
	health = 0;
	mana = 0;
};

/// <summary>
/// Creates an instance of EntityStats with argument mana and health.
/// </summary>
EntityStats::EntityStats(unsigned int health, unsigned int mana)
{
	if (health > 100) health = 100;
	if (mana > 100) mana = 100;

	EntityStats::health = health;
	EntityStats::mana = mana;
}

/// <summary>
/// Returns the current health value
/// </summary>
unsigned int EntityStats::GetHealth()
{
	return health;
}

/// <summary>
/// Returns the current mana value
/// </summary>
unsigned int EntityStats::GetMana()
{
	return mana;
}

/// <summary>
/// Sets the health value to passed value
/// </summary>
void EntityStats::SetHealth(unsigned int value)
{
	health = value;
}

/// <summary>
/// Sets the mana value to passed value
/// </summary>
void EntityStats::SetMana(unsigned int value)
{
	mana = value;
}