//
// Created by Winter on 01/10/2022.
//

#include "world/World.h"
#include "SFML/System/Vector2.hpp"
#include "util/SimplexNoise.h"
#include "GameAssets.h"
#include "world/Bush.h"
#include "world/Monster.h"
#include "world/Solid.h"

World::World(wiz::AssetLoader& assets)
		: assets(assets),
		  player(*this),
		  terrainMap(),
          entityMap(),
		  terrain_textures() {
	terrain_textures[TerrainType::GRASS] = assets.get(GameAssets::GRASS_TERRAIN);
	terrain_textures[TerrainType::WATER] = assets.get(GameAssets::WATER_TERRAIN);
	terrain_textures[TerrainType::SAND] = assets.get(GameAssets::SAND_TERRAIN);

    addEntity(&player);

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
			else if(noise > 0.5f && noise < 0.9f)
                addEntity(new Bush(*this, sf::Vector2i(i, j)));
		}
	}

    Entity* bat1 = new Monster(*this, sf::Vector2i(2, 1));
    Entity* bat2 = new Monster(*this, sf::Vector2i(-2, -1));

    addEntity(bat1);
    addEntity(bat2);
}

TerrainType World::getTerrainType(sf::Vector2i position) const {
	if(terrainMap.contains(position))
		return terrainMap.at(position);
	return TerrainType::GRASS;
}

const std::vector<Entity*>& World::getEntities() const {
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

bool World::tileOccupied(sf::Vector2i tile, Entity* exclude) {

	if(terrainMap[tile] == WATER)
		return true;

	int solid_range = 1;

	for(int i = -solid_range; i <= solid_range; i++) {
		for(int j = -solid_range; j <= solid_range; j++) {
			for(Entity* entity : entityMap[tile + sf::Vector2i{i, j}]) {
                if (entity == exclude)
                    continue;

				Solid* solid = dynamic_cast<Solid*>(entity);

				if(solid && solid->isBlocking(tile))
					return true;
			}
		}
	}

	return false;
}

void World::tick(float delta) {
    for (Entity *entity : entities) {
        entity->tick(delta);
    }
}

const std::vector<Entity *> &World::getEntitiesAt(sf::Vector2i position) const {
    return entityMap.contains(position) ?  entityMap.at(position) : empty;
}

void World::addEntity(Entity* entity) {
    entities.push_back(entity);
    if (entityMap.contains(entity->getPosition()))
        entityMap[entity->getPosition()].push_back(entity);
    else
        entityMap[entity->getPosition()] = {entity};
}

void World::moveEntity(sf::Vector2i oldPosition, Entity *entity) {
    std::remove(entityMap[oldPosition].begin(), entityMap[oldPosition].end(),entity);

	if (entityMap.contains(entity->getPosition()))
		entityMap[entity->getPosition()].push_back(entity);
	else
		entityMap[entity->getPosition()] = {entity};
}

void World::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	sf::Vector2f viewSize = { 16.0f, 9.0f };

	sf::Vector2i start = getPlayer().getPosition() - sf::Vector2i(static_cast<int>(ceil(viewSize.x / 2.0f)),
																  static_cast<int>(ceil(viewSize.y / 2.0f))) - sf::Vector2i{1,1};
	sf::Vector2i end = getPlayer().getPosition() + sf::Vector2i(static_cast<int>(floor(viewSize.x / 2.0f)),
																static_cast<int>(floor(viewSize.y / 2.0f))) + sf::Vector2i{1,1};

	for(int i = start.x; i <= end.x; i++) {
		for(int j = start.y; j <= end.y; j++) {
			terrain_sprite.setTexture(*terrain_textures.at(this->getTerrainType({i, j})), true);
			terrain_sprite.setPosition({static_cast<float>(i), -static_cast<float>(j)});
			terrain_sprite.setScale({1.0f / terrain_sprite.getTexture()->getSize().x,
									 1.0f / terrain_sprite.getTexture()->getSize().y});
			target.draw(terrain_sprite);
		}
	}

	for(Entity* entity : getEntities())
		if(entity->getPosition().x >= start.x
		   && entity->getPosition().y >= start.y
		   && entity->getPosition().x <= end.x
		   && entity->getPosition().y <= end.y)
			entityDrawList.push_back(entity);

	std::sort(entityDrawList.begin(), entityDrawList.end(), [](Entity* a, Entity* b) {
		return a->getPosition().y > b->getPosition().y
			|| a->getPosition().y == b->getPosition().y
			&& (a->getZOrder() < b->getZOrder()
			|| a->getZOrder() == b->getZOrder()
			&& a->getPosition().x > b->getPosition().x);
	});

	for(sf::Drawable* drawable : entityDrawList)
		target.draw(*drawable);
	entityDrawList.clear();
}
