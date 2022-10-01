//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_ENTITY_H
#define LD51_CLIENT_ENTITY_H


#include "SFML/System/Vector2.hpp"
#include "Tickable.h"

class Entity : public Tickable {
public:
	virtual ~Entity() = default;

	virtual sf::Vector2i getPosition() const = 0;

	inline int x() const {
		return getPosition().x;
	}

	inline int y() const {
		return getPosition().y;
	}
};


#endif //LD51_CLIENT_ENTITY_H
