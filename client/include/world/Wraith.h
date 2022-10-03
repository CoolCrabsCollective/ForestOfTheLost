//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_WRAITH_H
#define LD51_CLIENT_WRAITH_H


#include <SFML/System/Vector2.hpp>
#include "Monster.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class Wraith : public Monster {
public:
    explicit Wraith(World &world, sf::Vector2i position);
protected:
};

#endif //LD51_CLIENT_WRAITH_H
