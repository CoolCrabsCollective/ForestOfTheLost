//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_ENTITY_H
#define LD51_CLIENT_ENTITY_H


#include "SFML/System/Vector2.hpp"
#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"

class World;

class Entity : public Tickable, public sf::Drawable {
protected:
	World& world;
	sf::Vector2i position = {};
public:
	Entity(World& world) : world(world) {}

	virtual ~Entity() = default;

	inline World& getWorld() {
		return world;
	}

	inline const World& getWorld() const {
		return world;
	}

	inline sf::Vector2i getPosition() const {
		return position;
	}

	inline int x() const {
		return getPosition().x;
	}

	inline int y() const {
		return getPosition().y;
	}
};


#endif //LD51_CLIENT_ENTITY_H
