#ifndef ENTITY_H
#define ENTITY_H

#include "EntityStats.h"
#include "Object.h"

class Entity: public Object
{
protected:
	EntityStats stats;

public:
	Entity() {};
};

#endif