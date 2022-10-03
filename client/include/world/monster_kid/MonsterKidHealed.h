//
// Created by Winter on 03/10/2022.
//

#ifndef LD51_CLIENT_MONSTERKIDHEALED_H
#define LD51_CLIENT_MONSTERKIDHEALED_H


#include "world/NPC.h"

class MonsterKidHealed : public NPC  {
public:
	MonsterKidHealed(World& world, const sf::Vector2i& position);

	bool activate() override;
};


#endif //LD51_CLIENT_MONSTERKIDHEALED_H
