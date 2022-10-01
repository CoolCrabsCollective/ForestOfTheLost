//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_PLAYER_H
#define LD51_CLIENT_PLAYER_H


#include "Entity.h"

class Player : public Entity {
	sf::Vector2i position;

public:
	sf::Vector2i getPosition() override;
};


#endif //LD51_CLIENT_PLAYER_H
