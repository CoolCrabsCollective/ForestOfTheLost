//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_WORLD_H
#define LD51_CLIENT_WORLD_H

#include <vector>
#include "Terrain.h"
#include "SFML/System/Vector2.hpp"
#include "Player.h"
#include "WIZ/asset/AssetLoader.h"

class Entity;
class Player;

struct VecCompare {
	bool operator() (const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
		return lhs.x < rhs.x || lhs.x == rhs.x && lhs.y < rhs.y;
	}
};

class World : public Tickable {
	wiz::AssetLoader& assets;
	std::vector<Entity*> entities;
	Player player;

	std::map<sf::Vector2i, TerrainType, VecCompare> terrainMap;
    std::map<sf::Vector2i, std::vector<Entity*>, VecCompare> entityMap;
    std::vector<Entity*> empty = {};

public:
	World(wiz::AssetLoader& assets);

	TerrainType getTerrainType(sf::Vector2i position);

	const std::vector<Entity*>& getEntities() const;

	const Player& getPlayer() const;

	Player& getPlayer();

	wiz::AssetLoader& getAssets();

    bool tileOccupied(sf::Vector2i tile, Entity *exclude);

    void tick(float delta) override;

    const std::vector<Entity*>& getEntitiesAt(sf::Vector2i position) const;

    void addEntity(Entity* entity);

    void moveEntity(sf::Vector2i oldPosition, Entity* entity);
};


#endif //LD51_CLIENT_WORLD_H
