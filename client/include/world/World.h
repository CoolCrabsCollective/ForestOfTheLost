//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_WORLD_H
#define LD51_CLIENT_WORLD_H

#include <vector>
#include "Terrain.h"
#include "SFML/System/Vector2.hpp"
#include "Entity.h"

class World {
public:
	TerrainType getTerrainType(sf::Vector2i position);

	std::vector<Entity> getEntities();
};


#endif //LD51_CLIENT_WORLD_H
