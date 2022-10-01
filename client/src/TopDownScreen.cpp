//
// Created by Winter on 01/10/2022.
//

#include "TopDownScreen.h"
#include "GameAssets.h"

TopDownScreen::TopDownScreen(wiz::Game& game)
		: Screen(game), world(), terrain_textures() {
}

void TopDownScreen::tick(float delta) {

}

void TopDownScreen::render(sf::RenderTarget& target) {
	sf::Vector2f viewSize = {16.0f, 9.0f};

	frameBuffer.create(1280, 720);
	frameBuffer.clear();
	frameBuffer.setView(sf::View({ world.getPlayer().x() + 0.5f, world.getPlayer().y() + 0.5f }, viewSize));
	target.clear();

	sf::Vector2i start = world.getPlayer().getPosition() - sf::Vector2i(static_cast<int>(ceil(viewSize.x / 2.0f)),
																		 static_cast<int>(ceil(viewSize.y / 2.0f)));
	sf::Vector2i end = world.getPlayer().getPosition() + sf::Vector2i(static_cast<int>(floor(viewSize.x / 2.0f)),
																	  static_cast<int>(floor(viewSize.y / 2.0f)));
	for(int i = start.x; i <= end.x; i++) {
		for(int j = start.y; j <= end.y; j++) {
            terrain_sprite.setTexture(*terrain_textures[world.getTerrainType({i, j})]);
			terrain_sprite.setPosition({static_cast<float>(i), static_cast<float>(j)});
			terrain_sprite.setScale({1.0f / terrain_sprite.getTexture()->getSize().x, 1.0f / terrain_sprite.getTexture()->getSize().y});
            frameBuffer.draw(terrain_sprite);

            if (i % 4 == 0 && j % 3 == 0) {
                hiding_spot_sprite.setPosition({static_cast<float>(i), static_cast<float>(j)});
                hiding_spot_sprite.setScale({1.0f / hiding_spot_sprite.getTexture()->getSize().x, 1.0f / hiding_spot_sprite.getTexture()->getSize().y});
                frameBuffert .draw(hiding_spot_sprite);
            }

		}
	}

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

    hiding_spot_sprite.setTexture(*getGame().getAssets().get(GameAssets::HIDING_SPOT));
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