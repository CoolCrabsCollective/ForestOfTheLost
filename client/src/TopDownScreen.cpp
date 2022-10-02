//
// Created by Winter on 01/10/2022.
//

#include <iostream>
#include "TopDownScreen.h"
#include "GameAssets.h"
#include "world/HidingSpot.h"
#include "world/Monster.h"
#include "WIZ/input/Mapping.h"
#include "WIZ/input/MappingDatabase.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game), world(game.getAssets()) {
    endGoalText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
    endGoalText.setCharacterSize(50);
    endGoalText.setString("Congrats you have reached the endpoint...");
    sf::FloatRect bounds = endGoalText.getLocalBounds();
    endGoalText.setPosition(sf::Vector2f(600 - bounds.getSize().x / 2, 450 - bounds.getSize().y / 2));
}

void TopDownScreen::tick(float delta) {
    processInput();

    if(world.isEndPointReached())
        return;

    world.tick(delta);
}

bool TopDownScreen::isInteractPressed() {
	if(sf::Joystick::isConnected(0)) {

		const wiz::Mapping& mapping = wiz::MappingDatabase::getInstance().getMapping(sf::Joystick::getIdentification(0).name);

		if(mapping.hasButton(wiz::MapButton::A) && sf::Joystick::isButtonPressed(0, mapping.getButton(wiz::MapButton::A))
			|| mapping.hasButton(wiz::MapButton::B) && sf::Joystick::isButtonPressed(0, mapping.getButton(wiz::MapButton::B)))
			return true;
	}

	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I);
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
                        || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < 0;

    bool southPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)
                        || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 0;

	bool interactPressed = isInteractPressed();

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
    if (world.isEndPointReached()) {
        target.draw(endGoalText);
        return;
    }

    if(!frameBuffer.create(1280, 720))
        throw std::runtime_error("Failed to create FBO!");

    frameBuffer.clear();
    frameBuffer.setView(sf::View({ world.getPlayer().getRenderPosition().x + 0.5f,
								   -world.getPlayer().getRenderPosition().y + 0.5f }, World::VIEW_SIZE));
	drawWorld(frameBuffer);

	spookyShader->setUniform("timeAccumulator", world.getTimeAccumulator());
	spookyShader->setUniform("grayscaleness", world.getGrayscaleness());
	frameBuffer.display(); // done drawing fbo
	sf::Sprite fbo(frameBuffer.getTexture());
	target.clear();
	target.draw(fbo, spookyShader);
	drawEyes(target);
	drawUI(target);
}

void TopDownScreen::drawEyes(sf::RenderTarget &target) {
    sf::Vector2f viewSize = World::VIEW_SIZE;
    target.setView(sf::View({ world.getPlayer().getRenderPosition().x + 0.5f, -world.getPlayer().getRenderPosition().y + 0.5f }, viewSize));

    eyesShader->setUniform("timeAccumulator", world.getTimeAccumulator());
    for(auto entity : world.getEntities())
    {
        if(Monster* monster = dynamic_cast<Monster*>(entity))
        {
            sf::Glsl::Vec2 monster_screen { monster->getRenderPosition().x - world.getPlayer().getRenderPosition().x / 1080.0f, monster->getRenderPosition().y - world.getPlayer().getRenderPosition().y / 720.0f };

            //eyesShader->setUniform("monster_screen_coords", monster_screen);
            eye_sprite.setPosition(sf::Vector2f {static_cast<float>(monster->getRenderPosition().x), -static_cast<float>(monster->getRenderPosition().y)});
            target.draw(eye_sprite, eyesShader);
        }
    }
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
	getGame().addWindowListener(this);
	getGame().addInputListener(this);

    heart_sprite.setTexture(*getAssets().get(GameAssets::HEART));
    heart_sprite.setScale({ 50.0f * 7.0f / 8.0f / heart_sprite.getTexture()->getSize().x,
                            50.0f * 7.0f / 8.0f / heart_sprite.getTexture()->getSize().y });

    eye_sprite.setTexture(*getAssets().get(GameAssets::SPOOKY_EYES));
    eye_sprite.setScale({ 1.0f / eye_sprite.getTexture()->getSize().x, 1.0f / eye_sprite.getTexture()->getSize().y });

    spookyShader = getAssets().get(GameAssets::SPOOKY_SHADER);
    eyesShader = getAssets().get(GameAssets::EYES_SHADER);
}

void TopDownScreen::hide() {
	getGame().removeWindowListener(this);
	getGame().removeInputListener(this);
}

const std::string& TopDownScreen::getName() const {
	return name;
}

void TopDownScreen::windowClosed() {
	getGame().getWindow().close();
}
