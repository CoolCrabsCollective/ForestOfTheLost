//
// Created by cedric on 2022-10-01.
//

#include "world/TeddyBear.h"
#include "GameAssets.h"

TeddyBear::TeddyBear(World &world, sf::Vector2i position)
	: Item(world, world.getAssets().get(GameAssets::ITEM_TEDDY), position) {

}

bool TeddyBear::activate() {
	if(taken || world.isChangingPhase())
		return false;

	world.getDialogBox().startDialog({ "You found an old dirty teddy bear." }, [&]() {
		taken = true;
		world.changePhaseIn(2);
        world.resetAccumulator();
	});
	return true;
}
