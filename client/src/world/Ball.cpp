//
// Created by Winter on 03/10/2022.
//

#include "world/Ball.h"
#include "GameAssets.h"

Ball::Ball(World& world, sf::Vector2i position)
		: Item(world, world.getAssets().get(GameAssets::ITEM_BALL), position) {

}

bool Ball::activate() {
	if(taken)
		return false;

	world.getDialogBox().startDialog({ "You found an old ball." }, [&]() {
		taken = true;
		world.removeBalls();
	});
	return true;
}
