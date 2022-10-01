//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_WORLD_H
#define LD51_CLIENT_WORLD_H

#include <vector>
#include "Terrain.h"
#include "SFML/System/Vector2.hpp"
#include "Player.h"

class Entity;
class Player;

class World {
	std::vector<Entity> entities;
	Player player;

public:
	TerrainType getTerrainType(sf::Vector2i position);

	const std::vector<Entity>& getEntities() const;

	std::vector<Entity>& getEntities();

	const Player& getPlayer() const;

	Player& getPlayer();



};


#endif //LD51_CLIENT_WORLD_H
