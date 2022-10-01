//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_ENTITY_H
#define LD51_CLIENT_ENTITY_H


#include "SFML/System/Vector2.hpp"

class Entity {
public:
	virtual ~Entity() = default;

	virtual sf::Vector2i getPosition() = 0;
};


#endif //LD51_CLIENT_ENTITY_H
