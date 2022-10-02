//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_TOPDOWNSCREEN_H
#define LD51_CLIENT_TOPDOWNSCREEN_H

#include <WIZ/game/Screen.h>
#include <unordered_map>
#include <SFML/Graphics/RenderTexture.hpp>
#include "world/World.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "WIZ/input/MappingDatabase.h"

class TopDownScreen : public wiz::Screen, public wiz::WindowListener, public wiz::InputListener {
	std::string name = "TopDownScreen";

	World world;
	sf::Sprite heart_sprite;
	sf::Sprite eye_sprite;
	sf::RenderTexture frameBuffer;
    sf::Shader* spookyShader = nullptr;
    sf::Shader* eyesShader = nullptr;

    sf::Text endGoalText;

	wiz::MappingDatabase mappingDatabase;

    void processInput();
	bool isInteractPressed();

public:
	explicit TopDownScreen(wiz::Game& game);

	void drawWorld(sf::RenderTarget& target);

	void drawEyes(sf::RenderTarget& target);

	void drawUI(sf::RenderTarget& target);

	void tick(float delta) override;

	void render(sf::RenderTarget& target) override;

	void show() override;

	void hide() override;

	const std::string& getName() const override;

	void windowClosed() override;
};


#endif //LD51_CLIENT_TOPDOWNSCREEN_H
