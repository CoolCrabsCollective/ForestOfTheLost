//
// Created by Winter on 01/10/2022.
//

#include "world/World.h"

TerrainType World::getTerrainType(sf::Vector2i position) {
    if (position.x % 2 == 0)
        return TerrainType::HIDING_SPOT;

	return TerrainType::GRASS;
}

const std::vector<Entity>& World::getEntities() const {
	return entities;
}

std::vector<Entity>& World::getEntities() {
	return entities;
}

const Player& World::getPlayer() const {
	return player;
}

Player& World::getPlayer() {
	return player;
}
