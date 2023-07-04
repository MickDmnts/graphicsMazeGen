#pragma once

class EntityStats
{
private:
	unsigned int health;
	unsigned int mana;

public:
	EntityStats();
	EntityStats(unsigned int health, unsigned int mana);
	unsigned int GetHealth();
	unsigned int GetMana();
	void SetHealth(unsigned int value);
	void SetMana(unsigned int value);
};