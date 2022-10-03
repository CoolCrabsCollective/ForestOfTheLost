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
		: Screen(game),
	      dialogBox(game.getAssets().get(GameAssets::VT323_TTF), game.getAssets().get(GameAssets::DIALOG_BOX)),
		  world(game.getAssets(), dialogBox),
          mappingDatabase(),
          lily(*game.getAssets().get(GameAssets::LILY)),
          inspector_thinking(*game.getAssets().get(GameAssets::PLAYER_LEFT)){

	game.getAssets().get(GameAssets::SUSPICIOUS_FOREST_MUSIC)->play();

    endGoalText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
    endGoalText.setCharacterSize(50);
    endGoalText.setString("Congrats you have reached the endpoint...");
    sf::FloatRect bounds = endGoalText.getLocalBounds();
    endGoalText.setPosition(sf::Vector2f(600 - bounds.getSize().x / 2, 450 - bounds.getSize().y / 2));

    dialogBox.startDialog({
        "Another kid lost in this forest...",
        "Why is is always the kids...",
        "I need to find her...",
        });

	mappingDatabase.loadFromCSV(*getGame().getAssets().get(GameAssets::CONTROLLER_DB));

    lily.setPosition({static_cast<float>((1280 / 2) - (lily.getTexture()->getSize().x * 16 / 2)) - 100, 30});
    lily.setScale({16, 16});

    inspector_thinking.setPosition({static_cast<float>(1280 / 2) + 200, 50});
    inspector_thinking.setScale({16, 16});

    dialogBox.callback = [&]() {
        drawLily = false;
    };
}

void TopDownScreen::tick(float delta) {
    processInput();

    dialogBox.tick(delta);

    fps = 1.0f / delta * 1000.0f;

    if(world.isEndPointReached() || dialogBox.isInProgress())
        return;

    world.tick(delta);
}

bool TopDownScreen::isInteractPressed() {
	if(sf::Joystick::isConnected(0)) {

		std::string name = sf::Joystick::getIdentification(0).name;

		if(mappingDatabase.hasMapping(name))
		{
			const wiz::Mapping& mapping = mappingDatabase.getMapping(name);

			if(mapping.hasButton(wiz::MapButton::A) && sf::Joystick::isButtonPressed(0, mapping.getButton(wiz::MapButton::A))
			   || mapping.hasButton(wiz::MapButton::B) && sf::Joystick::isButtonPressed(0, mapping.getButton(wiz::MapButton::B)))
				return true;
		}
	}

	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I);
}

void TopDownScreen::processInput() {

    was_interact_pressed = is_interact_pressed;
	bool connected = sf::Joystick::isConnected(0);

    bool eastPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
                        || connected && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50;

    bool northPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)
                        || connected && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -50;

    bool westPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
                        || connected && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50;

    bool southPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)
                        || connected && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 50;

	is_interact_pressed = isInteractPressed();

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

    if(was_interact_pressed && !is_interact_pressed)
    {
	    if(dialogBox.isInProgress())
	        dialogBox.interact();
	    else
            world.getPlayer().interact();
    }
}


void TopDownScreen::drawWorld(sf::RenderTarget &target) {
    target.clear();
	target.draw(world);
}

void TopDownScreen::render(sf::RenderTarget& target) {

    if(world.isEndPointReached()) {
		target.clear();
        target.draw(endGoalText);
        return;
    }

    frameBuffer.clear();
    frameBuffer.setView(sf::View({ world.getPlayer().getRenderPosition().x + 0.5f,
								   -world.getPlayer().getRenderPosition().y + 0.5f }, World::VIEW_SIZE));
	drawWorld(frameBuffer);

	spookyShader->setUniform("timeAccumulator",  world.getTimeAccumulator());
	spookyShader->setUniform("grayscaleness", world.getGrayscaleness());
	spookyShader->setUniform("scan_effect", world.getScanEffect());
	frameBuffer.display(); // done drawing fbo
	fbo_sprite.setTexture(frameBuffer.getTexture());
	target.clear();

	if(world.getPhase() == INITIAL && !world.isChangingPhaseNext()) {
        target.draw(fbo_sprite);
    }
	else {
		float spookyness = (float)fmod(world.getTimeAccumulator(), 10000.0f) / 10000.0f;
		spookyShader->setUniform("spookyness",
								 world.isChangingPhaseNext()
								 ? spookyness
								 : 1.0f);

		target.draw(fbo_sprite, spookyShader);
	}

	frameBuffer.clear(sf::Color(0, 0, 0, 0));
    drawNight(frameBuffer);

	frameBuffer.display();
	fbo_sprite.setTexture(frameBuffer.getTexture());

	eyesShader->setUniform("timeAccumulator", world.getTimeAccumulator());
	target.draw(fbo_sprite, eyesShader);

	drawUI(target);
}

void TopDownScreen::drawNight(sf::RenderTarget &target) {
    sf::Vector2f viewSize = World::VIEW_SIZE;
    target.setView(sf::View({ world.getPlayer().getRenderPosition().x + 0.5f, -world.getPlayer().getRenderPosition().y + 0.5f }, viewSize));

    for(auto entity : world.getEntities())
        if(Monster* monster = dynamic_cast<Monster*>(entity))
           monster->drawDarkness(target);
}

void TopDownScreen::drawUI(sf::RenderTarget &target) {
    sf::Vector2f viewSize = {1280, 720};
    target.setView(sf::View({viewSize.x / 2.0f, viewSize.y / 2.0f}, viewSize ));

    if (drawLily)
    {
        target.clear(sf::Color(38, 92, 66));
        target.draw(lily);
        target.draw(inspector_thinking);
    }

    target.draw(dialogBox);
	fpsText.setString("FPS: " + std::to_string(fps));
	target.draw(fpsText);
}

void TopDownScreen::show() {
	getGame().addWindowListener(this);
	getGame().addInputListener(this);


	if(!frameBuffer.create(1280, 720))
		throw std::runtime_error("Failed to create FBO!");

    spookyShader = getAssets().get(GameAssets::SPOOKY_SHADER);
    eyesShader = getAssets().get(GameAssets::EYES_SHADER);

	fpsText.setString("FPS: ");
	fpsText.setPosition(sf::Vector2f(50, 650));
	fpsText.setCharacterSize(20);
	fpsText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
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

void TopDownScreen::keyReleased(const sf::Event::KeyEvent& keyEvent) {
	if(keyEvent.code == sf::Keyboard::Escape)
		world.generatePhase(static_cast<GamePhase>(world.getPhase() + 1));
}
