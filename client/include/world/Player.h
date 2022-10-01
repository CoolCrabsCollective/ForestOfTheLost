//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_PLAYER_H
#define LD51_CLIENT_PLAYER_H


#include "Entity.h"
#include "world/directions.h"

class Player : public Entity {
	sf::Vector2i position = {};
    sf::Vector2i destination = {};

    sf::Vector2f renderPosition = {};

    Direction currentDir = NORTH;
    Direction destinationDir = NORTH;

    std::optional<Direction> inputDir;

    float actionProgress = 0;



    float movingSpeed = 2.0;

    void rotateToHeading(sf::Vector2i direction);
    bool checkCollision();

public:
	sf::Vector2i getPosition() const override;
    sf::Vector2f getRenderPosition() const;
    void move(std::optional<Direction> direction);
    void tick(float delta) override;
};


#endif //LD51_CLIENT_PLAYER_H
