//
// Created by william on 01/10/22.
//

#include "world/Direction.h"

sf::Vector2i directionToUnitVector(Direction direction) {
    return {(direction >= 2 ? -1 : 1) * (direction % 2 == 0 ? 1 : 0),
            (direction >= 2 ? -1 : 1) * (direction % 2 == 1 ? 1 : 0)};
}