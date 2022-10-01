//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_SOLID_H
#define LD51_CLIENT_SOLID_H


#include "SFML/System/Vector2.hpp"

class Solid {
public:
	virtual ~Solid() = default;

	virtual bool isBlocking(sf::Vector2i vec) = 0;
};


#endif //LD51_CLIENT_SOLID_H
