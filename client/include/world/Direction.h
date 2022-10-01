//
// Created by william on 01/10/22.
//

#ifndef LD51_CLIENT_DIRECTION_H
#define LD51_CLIENT_DIRECTION_H

#include "SFML/System/Vector2.hpp"

enum Direction {
    EAST = 0,
    NORTH,
    WEST,
    SOUTH
};

sf::Vector2i directionToUnitVector(Direction direction);

#endif //LD51_CLIENT_DIRECTION_H
