#include "stdafx.h"
#include "Object.h"
#include <iostream>
#include "ServiceLocator.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::Object::Object()
{
	coord = sf::Vector2i(0, 0);
	persistent = false;
}

charlotte::Object::~Object()
{
	
}

bool charlotte::Object::operator<(const charlotte::Object& other)
	const
{
	return priority < other.priority;
}

charlotte::Object::Object(charlotte::Object& inst)
{
	this->coord = inst.coord;
	this->activated = inst.activated;
	this->persistent = inst.persistent;
	this->priority = inst.priority;
	this->update = inst.update;
	this->render = inst.render;
}

int32_t charlotte::Object::getID()
{
	return this->m_guid;
}