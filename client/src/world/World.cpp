//
// Created by Winter on 01/10/2022.
//

#include <world/Item.h>
#include <world/TeddyBear.h>
#include "world/World.h"
#include "SFML/System/Vector2.hpp"
#include "util/SimplexNoise.h"
#include "GameAssets.h"
#include "world/Bush.h"
#include "world/Monster.h"
#include "world/Solid.h"
#include "world/Tree.h"
#include "world/EndGoal.h"

World::World(wiz::AssetLoader& assets)
		: assets(assets),
		  player(*this),
		  terrainMap(),
          entityMap(),
		  terrain_textures() {
	terrain_textures[TerrainType::GRASS] = assets.get(GameAssets::GRASS_TERRAIN);
	terrain_textures[TerrainType::WATER] = assets.get(GameAssets::WATER_TERRAIN);
	terrain_textures[TerrainType::SAND] = assets.get(GameAssets::SAND_TERRAIN);

	srand(20221001);

	generatePhase(GamePhase::INITIAL);

    // Randomly place end goal
    //int endGoalX = -5;
    //int endGoalY = 5;
    //addEntity(new EndGoal(*this, sf::Vector2i(endGoalX, endGoalY)));

    Entity* bat1 = new Monster(*this, sf::Vector2i(0, 1));
    Entity* teddy_bear = new TeddyBear(*this, sf::Vector2i(1, 1));
    addEntity(bat1);
    addEntity(teddy_bear);
	changePhase = true;
}

void World::generatePhase(GamePhase phase) {

	for(Entity* entity : entities)
		if(entity != &player)
			free(entity);

	entities.clear();
	entityMap.clear();
	addEntity(&player);
	terrainMap.clear();

	double offsetX = rand() * 10.0 / RAND_MAX;
	double offsetY = rand() * 10.0 / RAND_MAX;

	for(int i = -200; i <= 200; i++) {
		for(int j = -200; j <= 200; j++) {
			double nx = i / 400.0 - 0.5 + offsetX;
			double ny = j / 400.0 - 0.5 + offsetY;

			nx *= 5.0;
			ny *= 5.0;

			double noise = SimplexNoise::noise(nx, ny);
			if(noise < -0.75)
				terrainMap[sf::Vector2i(i, j)] = TerrainType::WATER;
			else if(noise < -0.7)
				terrainMap[sf::Vector2i(i, j)] = TerrainType::SAND;

			if(noise > -0.75) {
				double nx2 = i / 400.0 - 0.5 + offsetX * 9.0;
				double ny2 = j / 400.0 - 0.5 + offsetY * 9.0;

				nx2 *= 5000.0;
				ny2 *= 5000.0;

				double noise2 = SimplexNoise::noise(nx2, ny2);

				if(noise2 > 0.9) {
					TreeType type;
					if(phase == GamePhase::INITIAL)
						type = TreeType::ALIVE;
					else if(phase == GamePhase::FIRST_ENCOUNTER)
						type = TreeType::DEAD;

					addEntity(new Tree(*this, { i, j }, type));
				}
				else if(noise2 > 0.5)
					addEntity(new Bush(*this, { i, j }));
			}

		}
	}

	if(phase == GamePhase::INITIAL)
		grayscaleness = 0.0;
	else if(phase == GamePhase::FIRST_ENCOUNTER)
		grayscaleness = 0.5;
	else
		grayscaleness = 1.0;
	currentPhase = phase;
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

				if(solid && solid->isBlocking(tile)) {
                    EndGoal *endGoal = dynamic_cast<EndGoal *>(solid);
                    if (endGoal)
                        endPointReached = true;

                    return true;
                }
			}
		}
	}

	return false;
}

void World::tick(float delta) {

	timeAccumulator += delta;
	tenSecAccumulator += delta;

	if(tenSecAccumulator > 9250.0 || tenSecAccumulator < 500.0)
		getPlayer().setLockMovement(true);
	else
		getPlayer().setLockMovement(false);

	if(tenSecAccumulator > 10000.0) {

		if(changePhase && currentPhase < FINAL) {
			generatePhase(static_cast<GamePhase>(currentPhase + 1));
			//changePhase = false;
		}

		for(int i = 0; i < getEntities().size(); i++) {
			if(Monster* monster = dynamic_cast<Monster*>(getEntities().at(i))) {
				// Don't want to go to the same bush
				monster->findNewSpot();
			}
		}

		tenSecAccumulator = fmod(tenSecAccumulator, 10000.0f);
	}

    for (Entity *entity : entities) {
        entity->tick(delta);
    }
}

const std::vector<Entity *> &World::getEntitiesAt(sf::Vector2i position) const {
    return entityMap.contains(position) ? entityMap.at(position) : empty;
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

	sf::Vector2f viewSize = VIEW_SIZE;

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

bool World::isEndPointReached() const {
    return endPointReached;
}
