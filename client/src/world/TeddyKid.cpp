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
	getWorld().getDialogBox().startDialog({"Kid: Thank you for bringing my teddy back",
										   "You: What are you doing here? Are you alone?",
										   "Kid: ...",
                                           "You: I'm looking for a little girl. Her name is Lily. Have you seen her?",
                                           "Kid: ...",
                                           "*He fades away*",
                                           }, [&](){
        world.generatePhase(GHOST);
	});
	return NPC::activate();
}
