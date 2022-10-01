//
// Created by Winter on 01/10/2022.
//

#include <iostream>
#include "TopDownScreen.h"
#include "GameAssets.h"
#include "world/HidingSpot.h"
#include "world/Monster.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game), world(game.getAssets()), terrain_textures() {
}

void TopDownScreen::tick(float delta) {
    timeAccumulator += delta;
    tenSecAccumulator += delta;

    if (tenSecAccumulator > 10000.0) {
        std::cout << "10 seconds passed!" << std::endl;
        tenSecAccumulator = 0;
    }

    processInput();

    world.tick(delta);
}

void TopDownScreen::processInput() {
    bool eastPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
                        || sf::Joystick::isButtonPressed(0, 0);

    bool northPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)
                        || sf::Joystick::isButtonPressed(0, 1);

    bool westPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
                        || sf::Joystick::isButtonPressed(0, 2);

    bool southPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)
                        || sf::Joystick::isButtonPressed(0, 2);

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
    sf::Vector2f viewSize = {16.0f, 9.0f};
    target.clear();

    sf::Vector2i start = world.getPlayer().getPosition() - sf::Vector2i(static_cast<int>(ceil(viewSize.x / 2.0f)),
                                                                        static_cast<int>(ceil(viewSize.y / 2.0f))) - sf::Vector2i{1,1};
    sf::Vector2i end = world.getPlayer().getPosition() + sf::Vector2i(static_cast<int>(floor(viewSize.x / 2.0f)),
                                                                      static_cast<int>(floor(viewSize.y / 2.0f))) + sf::Vector2i{1,1};

    for(int i = start.x; i <= end.x; i++) {
        for(int j = start.y; j <= end.y; j++) {
            terrain_sprite.setTexture(*terrain_textures[world.getTerrainType({i, j})]);
            terrain_sprite.setPosition({static_cast<float>(i), -static_cast<float>(j)});
            terrain_sprite.setScale({1.0f / terrain_sprite.getTexture()->getSize().x, 1.0f / terrain_sprite.getTexture()->getSize().y});
            target.draw(terrain_sprite);
        }
    }

    for(Entity* entity : world.getEntities())
        target.draw(*entity);
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
}

void TopDownScreen::show() {
    sf::Vector2f viewSize = {16.0f, 9.0f};
	getGame().addWindowListener(this);
	getGame().addInputListener(this);

    spookyShader = getAssets().get(GameAssets::SPOOKY_SHADER);
	terrain_textures[TerrainType::GRASS] = getGame().getAssets().get(GameAssets::GRASS_TERRAIN);
	terrain_textures[TerrainType::WATER] = getGame().getAssets().get(GameAssets::WATER_TERRAIN);
	terrain_textures[TerrainType::SAND] = getGame().getAssets().get(GameAssets::SAND_TERRAIN);

    Entity* hiding_spot1 = new HidingSpot(world, sf::Vector2i(1, 1));
    Entity* hiding_spot2 = new HidingSpot(world, sf::Vector2i(-1, 2));
    Entity* bat = new Monster(world, sf::Vector2i(2, 1));

    world.getEntities().push_back(hiding_spot1);
    world.getEntities().push_back(hiding_spot2);
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