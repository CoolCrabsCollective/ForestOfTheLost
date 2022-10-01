//
// Created by Winter on 01/10/2022.
//

#include "TopDownScreen.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game) {}

void TopDownScreen::tick(float delta) {

}

void TopDownScreen::render(sf::RenderTarget& target) {

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