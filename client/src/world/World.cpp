//
// Created by Winter on 01/10/2022.
//

#include "world/World.h"

TerrainType World::getTerrainType(sf::Vector2i position) {
	return TerrainType::GRASS;
}

const std::vector<Entity*>& World::getEntities() const {
	return entities;
}

std::vector<Entity*>& World::getEntities() {
	return entities;
}

const Player& World::getPlayer() const {
	return player;
}

Player& World::getPlayer() {
	return player;
}
