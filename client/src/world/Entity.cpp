//
// Created by Alexander Winter on 2022-10-02.
//

#include "world/World.h"
#include "world/Monster.h"

Entity::~Entity() {
	if(std::find(getWorld().getEntities().begin(), getWorld().getEntities().end(), this) != getWorld().getEntities().end())
		throw std::runtime_error("EUEUEUEUE Found entity to be inside entities in destruction");

	if(std::find(getWorld().getEntitiesAt(getPosition()).begin(),
				 getWorld().getEntitiesAt(getPosition()).end(), this) != getWorld().getEntitiesAt(getPosition()).end())
		throw std::runtime_error("Found entity to be inside entity map in destruction");

	if(Monster* monster = dynamic_cast<Monster*>(this))
		if(std::find(getWorld().get_monsters().begin(), getWorld().get_monsters().end(),monster) != getWorld().get_monsters().end())
			throw std::runtime_error("Found entity to be inside monster list in destruction");
}