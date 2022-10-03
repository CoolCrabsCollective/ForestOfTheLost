//
// Created by Winter on 03/10/2022.
//

#include "world/monster_kid/MonsterKidMonster.h"
#include "GameAssets.h"

MonsterKidMonster::MonsterKidMonster(World& world,
									 const sf::Vector2i& position)
		: Monster(world, position,
				  world.getAssets().get(GameAssets::MONSTER_KID_MONSTER),
				  world.getAssets().get(GameAssets::MONSTER_KID_MONSTER)) {
	scale = 2.0;
	scaleDark = 2.0;

}