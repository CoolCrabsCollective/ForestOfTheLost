//
// Created by Winter on 01/10/2022.
//

#include <iostream>
#include "TopDownScreen.h"
#include "GameAssets.h"
#include "world/HidingSpot.h"
#include "world/Monster.h"
#include "WIZ/input/Mapping.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game), world(game.getAssets()) {
}

void TopDownScreen::tick(float delta) {
    timeAccumulator += delta;
    tenSecAccumulator += delta;

    if (tenSecAccumulator > 10000.0) {
        std::cout << "10 seconds passed!" << std::endl;

        for (int i = 0 ; i < world.getEntities().size() ; i++) {
            if(Monster* monster = dynamic_cast<Monster*>(world.getEntities().at(i))) {
                // Don't want to go to the same bush
                monster->findNewSpot();
            }
        }

        tenSecAccumulator = 0;
    }

    processInput();

    world.tick(delta);
}

void TopDownScreen::processInput() {

    bool eastPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
                        || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 0;

    bool northPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)
                        || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < 0;

    bool westPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
                        ||  sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < 0;

    bool southPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)
                        ||  sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 0;

    if (eastPressed && !westPressed)
        world.getPlayer().move(EAST);
    else if (northPressed && !southPressed)
        world.getPlayer().move(NORTH);
    else if (westPressed && !eastPressed)
        world.getPlayer().move(WEST);
    else if (southPressed && !northPressed)
        world.getPlayer().move(SOUTH);
    else
		world.getPlayer().move({});
}


void TopDownScreen::drawWorld(sf::RenderTarget &target) {
    target.clear();
	target.draw(world);
}

void TopDownScreen::render(sf::RenderTarget& target) {
    sf::Vector2f viewSize = {16.0f, 9.0f};

    frameBuffer.create(1280, 720);
    frameBuffer.clear();
    frameBuffer.setView(sf::View({ world.getPlayer().getRenderPosition().x + 0.5f, -world.getPlayer().getRenderPosition().y + 0.5f }, viewSize));
	drawWorld(frameBuffer);

	spookyShader->setUniform("timeAccumulator", timeAccumulator);
	frameBuffer.display(); // done drawing fbo
	sf::Sprite fbo(frameBuffer.getTexture());
	target.clear();
	target.draw(fbo, spookyShader);
	drawUI(target);
}


void TopDownScreen::drawUI(sf::RenderTarget &target) {
    sf::Vector2f viewSize = {1280, 720};
    target.setView(sf::View({viewSize.x / 2.0f, viewSize.y / 2.0f}, viewSize ));
    for (int i = 0; i < world.getPlayer().get_health(); i++)
    {
        heart_sprite.setPosition({static_cast<float>(50 + 50* i), 50});
        target.draw(heart_sprite);
    }
}


void TopDownScreen::show() {
    sf::Vector2f viewSize = {16.0f, 9.0f};
	getGame().addWindowListener(this);
	getGame().addInputListener(this);

    heart_sprite.setTexture(*getAssets().get(GameAssets::HEART));
    heart_sprite.setScale({ 50.0f * 7.0f / 8.0f / heart_sprite.getTexture()->getSize().x, 50.0f * 7.0f / 8.0f / heart_sprite.getTexture()->getSize().y });
    spookyShader = getAssets().get(GameAssets::SPOOKY_SHADER);

    Entity* hiding_spot1 = new HidingSpot(world, sf::Vector2i(1, 1));
    Entity* hiding_spot2 = new HidingSpot(world, sf::Vector2i(-1, 2));
    world.getEntities().push_back(hiding_spot1);
    world.getEntities().push_back(hiding_spot2);
    Entity* bat = new Monster(world, sf::Vector2i(2, 1));

    world.getEntities().push_back(bat);
}

void TopDownScreen::hide() {
	getGame().removeWindowListener(this);
	getGame().removeWindowListener(this);
}

const std::string& TopDownScreen::getName() const {
	return name;
}

void TopDownScreen::windowClosed() {
	getGame().getWindow().close();
}
