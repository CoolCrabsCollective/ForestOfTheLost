//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_PLAYER_H
#define LD51_CLIENT_PLAYER_H


#include "Entity.h"

class Player : public Entity {
	sf::Vector2i position;
    sf::Vector2f renderPosition;

    sf::Vector2i heading;

    void rotateToHeading(sf::Vector2i direction);
    bool checkCollision();

public:
	sf::Vector2i getPosition() const override;
    void move(sf::Vector2i direction);
};


#endif //LD51_CLIENT_PLAYER_H
