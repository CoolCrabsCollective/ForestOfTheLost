//
// Created by cedric on 2022-10-03.
//

#ifndef LD51_CLIENT_SKULL_H
#define LD51_CLIENT_SKULL_H


#include "Monster.h"

class Skull : public Monster {
public:
    explicit Skull(World &world, sf::Vector2i position);
protected:
};


#endif //LD51_CLIENT_SKULL_H
