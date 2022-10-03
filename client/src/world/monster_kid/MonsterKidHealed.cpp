//
// Created by Winter on 03/10/2022.
//

#include "world/monster_kid/MonsterKidHealed.h"
#include "GameAssets.h"
#include "world/World.h"

MonsterKidHealed::MonsterKidHealed(World& world,
								   const sf::Vector2i& position)
								   : NPC(world, position, {{NORTH, world.getAssets().get(GameAssets::CRYING_GIRL_BACK)},
														   {SOUTH, world.getAssets().get(GameAssets::CRYING_GIRL_FRONT)},
														   {EAST, world.getAssets().get(GameAssets::CRYING_GIRL_RIGHT)},
														   {WEST, world.getAssets().get(GameAssets::CRYING_GIRL_LEFT)}}) {

}

bool MonsterKidHealed::activate() {
	getWorld().getDialogBox().startDialog({"Kid: I don't know what happened to me, but I feel much better now.",
										   "Kid: Thank you for playing with me one last time..."});

	return NPC::activate();
}
