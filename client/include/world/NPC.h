//
// Created by Winter on 02/10/2022.
//

#ifndef LD51_CLIENT_NPC_H
#define LD51_CLIENT_NPC_H


#include <map>
#include "Entity.h"
#include "Solid.h"
#include "Interactable.h"
#include "Direction.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class NPC : public Entity, public Solid, public Interactable {

	Direction currentDir = NORTH;
	mutable sf::Sprite sprite;
	std::map<Direction, sf::Texture*> textureMap;

public:
	NPC(World& world, sf::Vector2i position, std::map<Direction, sf::Texture*> textureMap);

	bool activate() override;

	bool isBlocking(sf::Vector2i vec) override;

	void tick(float delta) override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD51_CLIENT_NPC_H
