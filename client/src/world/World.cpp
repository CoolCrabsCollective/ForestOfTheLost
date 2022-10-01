//
// Created by Winter on 01/10/2022.
//

#include "world/World.h"
#include "SFML/System/Vector2.hpp"
#include "util/SimplexNoise.h"

World::World(wiz::AssetLoader& assets)
		: assets(assets),
		  player(*this),
		  terrainMap() {
	entities.push_back(&player);

	for(int i = -200; i <= 200; i++) {
		for(int j = -200; j <= 200; j++) {
			double nx = i / 400.0f - 0.5f;
			double ny = j / 400.0f - 0.5f;

			nx *= 5.0f;
			ny *= 5.0f;

			double noise = SimplexNoise::noise(nx, ny);
			if(noise < -0.75f)
				terrainMap[sf::Vector2i(i, j)] = TerrainType::WATER;
			else if(noise < -0.7f)
				terrainMap[sf::Vector2i(i, j)] = TerrainType::SAND;
		}
	}
}

TerrainType World::getTerrainType(sf::Vector2i position) {
	if(terrainMap.contains(position))
		return terrainMap[position];
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

wiz::AssetLoader& World::getAssets() {
	return assets;
}

bool World::tileOccupied(sf::Vector2i tile, Entity *exclude) {
	if(terrainMap[tile] == WATER)
		return true;

    for (Entity *entity : entities) {
        bool occupied = (tile == entity->getPosition() || (dynamic_cast<const Player*>(entity) != nullptr && tile == entity->getDestination())) && exclude != entity;
        if (occupied) {
            return true;
        }
    }

    return false;
}

void World::tick(float delta) {
    for (Entity *entity : entities) {
        entity->tick(delta);
    }
}
