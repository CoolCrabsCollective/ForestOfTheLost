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
    sf::Vector2i destination = {};
public:
	Entity(World& world) : world(world) {}

	~Entity() override;

	inline World& getWorld() {
		return world;
	}

	inline const World& getWorld() const {
		return world;
	}

	inline sf::Vector2i getPosition() const {
		return position;
	}

    inline void setPosition(sf::Vector2i pos) {
        position = pos;
    }

	virtual inline sf::Vector2f getRenderPosition() const {
		return sf::Vector2f(position);
	}

    inline sf::Vector2i getDestination() const {
        return destination;
    }

    inline void setDestination(sf::Vector2i des) {
        destination = des;
    }

	inline virtual int getZOrder() const {
		return 0;
	}
};

#endif //LD51_CLIENT_ENTITY_H
