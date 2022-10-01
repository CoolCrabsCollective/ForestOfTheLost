//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_PLAYER_H
#define LD51_CLIENT_PLAYER_H


#include <map>
#include "Entity.h"
#include "world/Direction.h"
#include <optional>
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "HealthComponent.h"

class Player : public Entity, public HealthComponent<int> {
    sf::Vector2i destination = {};

    sf::Vector2f renderPosition = {};

    Direction currentDir = NORTH;
    Direction destinationDir = NORTH;

    std::optional<Direction> inputDir;

    float actionProgress = 0;

    float movingSpeed = 2.0;
    float rotationSpeed = 1.0;

	mutable sf::Sprite sprite;
	std::map<Direction, sf::Texture*> textureMap;
public:
	Player(World& world);

    sf::Vector2f getRenderPosition() const;
    void move(std::optional<Direction> direction);
    void tick(float delta) override;


	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD51_CLIENT_PLAYER_H
