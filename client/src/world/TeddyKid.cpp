//
// Created by Winter on 02/10/2022.
//

#include "world/TeddyKid.h"
#include "world/World.h"
#include "GameAssets.h"

TeddyKid::TeddyKid(World& world, const sf::Vector2i& position)
		: NPC(world, position, {{NORTH, world.getAssets().get(GameAssets::TEDDY_KID_BACK)},
								{SOUTH, world.getAssets().get(GameAssets::TEDDY_KID_FRONT)},
								{EAST, world.getAssets().get(GameAssets::TEDDY_KID_RIGHT)},
								{WEST, world.getAssets().get(GameAssets::TEDDY_KID_LEFT)}}) {}

bool TeddyKid::activate() {
	getWorld().getDialogBox().startDialog({"Kid: Thank you for bringing Teddie here with me.",
										   "You: What are you doing here? Are you alone in this forest?",
										   "Kid: I don't know..."}, [&](){
        world.generatePhase(GHOST);
	});
	return NPC::activate();
}
