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
#include "DialogBox.h"
#include "WIZ/input/MappingDatabase.h"
#include "SFML/Audio/Music.hpp"

class TopDownScreen : public wiz::Screen, public wiz::WindowListener, public wiz::InputListener {
protected:
    std::string name = "TopDownScreen";

	DialogBox dialogBox;

	World world;
	sf::RenderTexture frameBuffer;
    sf::Shader* spookyShader = nullptr;
    sf::Shader* eyesShader = nullptr;

    sf::Text endGoalText, fpsText;

	wiz::MappingDatabase mappingDatabase;

    void processInput();
	bool isInteractPressed();

	bool is_interact_pressed = false;
    bool was_interact_pressed = false;

	float fps = 0.0f;

    sf::Sprite lily;
    sf::Sprite inspector_thinking;
    bool drawLily = true;

public:
	explicit TopDownScreen(wiz::Game& game);

	void drawWorld(sf::RenderTarget& target);

	void drawNight(sf::RenderTarget& target);

	void drawUI(sf::RenderTarget& target);

	void tick(float delta) override;

	void render(sf::RenderTarget& target) override;

	void show() override;

	void hide() override;

	const std::string& getName() const override;

	void windowClosed() override;
};


#endif //LD51_CLIENT_TOPDOWNSCREEN_H
