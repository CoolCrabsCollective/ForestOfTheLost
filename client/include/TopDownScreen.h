//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_TOPDOWNSCREEN_H
#define LD51_CLIENT_TOPDOWNSCREEN_H

#include <WIZ/game/Screen.h>

class TopDownScreen : public wiz::Screen, public wiz::WindowListener {
	std::string name = "TopDownScreen";
public:
	TopDownScreen(wiz::Game& game);

	void tick(float delta) override;

	void render(sf::RenderTarget& target) override;

	void show() override;

	void hide() override;

	const std::string& getName() const override;

	void windowClosed() override;
};


#endif //LD51_CLIENT_TOPDOWNSCREEN_H
