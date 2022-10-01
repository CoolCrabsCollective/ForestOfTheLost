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
#include "Alive.h"
#include "Solid.h"

class Player : public Entity, public Alive<int>, public Solid {
    sf::Vector2f renderPosition = {};

    Direction currentDir;
    Direction destinationDir;

    std::optional<Direction> inputDir;

    float actionProgress = 0;

    const float movingSpeed = 3.0;
    const float rotationSpeed = 50.0;

	mutable sf::Sprite sprite;
	std::map<Direction, sf::Texture*> textureMap;
public:
	Player(World& world);

    sf::Vector2f getRenderPosition() const;
    void move(std::optional<Direction> direction);
    void tick(float delta) override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    bool isBlocking(sf::Vector2i vec) override;

	int getZOrder() const override;
};


#endif //LD51_CLIENT_PLAYER_H
