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

	world.getDialogBox().startDialog({ "You found an old ball. The ghost mom said the monster kid likes toys, maybe I should try playing ball with him." }, [&]() {
		taken = true;
		world.setGotBalls(true);
		world.removeBalls();
	});
	return true;
}

void Ball::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
	if(taken)
		return;

	sprite.setPosition({static_cast<float>(position.x), static_cast<float>(-position.y)});
	sprite.setScale({ 0.5f / sprite.getTexture()->getSize().x, 0.5f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
