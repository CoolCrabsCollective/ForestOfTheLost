//
// Created by Winter on 03/10/2022.
//

#ifndef LD51_CLIENT_MONSTERKIDMONSTER_H
#define LD51_CLIENT_MONSTERKIDMONSTER_H


#include "world/Monster.h"

class MonsterKidMonster : public Monster {
public:
	MonsterKidMonster(World& world, const sf::Vector2i& position);
};


#endif //LD51_CLIENT_MONSTERKIDMONSTER_H
