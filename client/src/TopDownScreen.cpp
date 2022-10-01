//
// Created by Winter on 01/10/2022.
//

#include "TopDownScreen.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game), world() {}

void TopDownScreen::tick(float delta) {

}

void TopDownScreen::render(sf::RenderTarget& target) {

	target.clear();
	target.setView(sf::View({ world.getPlayer().x() + 0.5f, world.getPlayer().y() + 0.5f }, {16.0f, 9.0f}));
}

void TopDownScreen::show() {

}

void TopDownScreen::hide() {
	getGame().removeWindowListener(this);
}

const std::string& TopDownScreen::getName() const {
	return name;
}

void TopDownScreen::windowClosed() {
	getGame().getWindow().close();
}