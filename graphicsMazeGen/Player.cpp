#include "Player.h"
#include "EntityStats.h"

Player::Player()
{
	stats = EntityStats(0, 0);
}

Player::Player(unsigned int health, unsigned int mana)
{
	stats = EntityStats(health, mana);
}

EntityStats Player::GetStats()
{
	return stats;
}

void Player::ApplyDamageBy(unsigned int value)
{
	stats.SetHealth(stats.GetHealth() - value);
}