//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_GHOUL_H
#define LD51_CLIENT_GHOUL_H

#include "Monster.h"

class Ghoul : public Monster {
public:
    explicit Ghoul(World &world, sf::Vector2i position);
protected:
};


#endif //LD51_CLIENT_GHOUL_H
