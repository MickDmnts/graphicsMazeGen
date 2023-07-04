#pragma once

#include "EntityStats.h"

class Player
{
protected:
	EntityStats stats;

public:
	Player();
	Player(unsigned int health, unsigned int mana);
	EntityStats GetStats();
	void ApplyDamageBy(unsigned int value);
};