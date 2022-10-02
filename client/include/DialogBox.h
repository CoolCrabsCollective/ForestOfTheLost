//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_DIALOGBOX_H
#define LD51_CLIENT_DIALOGBOX_H


#include <vector>
#include <string>
#include <world/Entity.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <functional>

class DialogBox : public sf::Drawable, public Tickable {
public:
    explicit DialogBox(sf::Font* font, sf::Texture* texture);
    void interact();

    void tick(float delta) override;

    void startDialog(const std::vector<std::string>& dialog, std::function<void()> callback = [](){});

    bool isInProgress() const;

    std::vector<std::string> dialog;
    float currentTextProgressTime = 0.0f;

    mutable sf::Sprite sprite;
    mutable sf::Text text;
    sf::Font* font = nullptr;

	std::function<void()> callback = [](){};
	bool wasInProgress = false;

protected:
    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    int dialogIndex = 0;
    float maximumTextProgressTime = 5.0f;

    void next();
    void complete();
};


#endif //LD51_CLIENT_DIALOGBOX_H
