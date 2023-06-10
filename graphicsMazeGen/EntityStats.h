#ifndef ENTITY_STATS_H
#define ENTITY_STATS_H

class EntityStats
{
private:
	unsigned int health = 0;
	unsigned int mana = 0;

public:
	unsigned int GetHealth()
	{
		return health;
	}

	unsigned int GetMana()
	{
		return mana;
	}

	void SetHealth(unsigned int value)
	{
		health = value;
	}

	void SetMana(unsigned int value)
	{
		mana = value;
	}

	EntityStats()
	{
	}

	EntityStats(unsigned int health, unsigned int mana)
	{
		if (health > 100) health = 100;
		if (mana > 100) mana = 100;

		health = health;
		mana = mana;
	}
};
#endif
