//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_BAT_H
#define LD51_CLIENT_BAT_H


#include "Monster.h"

class Bat : public Monster {
public:
    explicit Bat(World &world, sf::Vector2i position);
protected:
};


#endif //LD51_CLIENT_BAT_H
