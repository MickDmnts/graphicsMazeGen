#ifndef PLAYER_H
#define PLAYER_H

#include "EntityStats.h"
#include "Entity.h"
#include "Camera.h"

class Player : private Entity
{
private:
	Camera playerCamera;

public:
	Player()
	{}

	Player(unsigned int health, unsigned int mana)
	{
		stats = EntityStats();
		playerCamera = Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f));

		stats.SetHealth(health);
		stats.SetMana(mana);
	}

	EntityStats GetStats()
	{return stats;}

	Camera GetCamera()
	{return playerCamera;}

	void ApplyDamageBy(unsigned int value)
	{stats.SetHealth(stats.GetHealth() - value);}
};
#endif
