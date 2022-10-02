//
// Created by cedric on 2022-10-02.
//

#include "DialogBox.h"

#include <utility>
#include <SFML/Graphics.hpp>

DialogBox::DialogBox(sf::Font* font, sf::Texture* texture) : font(font), sprite(*texture){

}

void DialogBox::interact() {
    if(currentTextProgressTime < maximumTextProgressTime)
        complete();
    else
        next();
}

void DialogBox::tick(float delta) {
    currentTextProgressTime += delta / 1000.0f;

	if(!isInProgress() && wasInProgress) {
		callback();
		callback = [](){};
	}

	wasInProgress = isInProgress();
}

void DialogBox::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if(!this->isInProgress())
        return;

    float dialog_ratio = currentTextProgressTime / maximumTextProgressTime;

    int characters_to_show = dialog[dialogIndex].size() * dialog_ratio;
    std::string incomplete_text = dialog[dialogIndex].substr(0, characters_to_show);

    sprite.setPosition({ 60.0f, 620.0f - 50.0f});
    sprite.setScale({ 4.0f, 4.0f });
    target.draw(sprite);

    text.setFont(*font);
    text.setString(incomplete_text);
    text.setScale( { 1.0f, 1.0f});
    text.setPosition({70.0f, 620.0f - 30.0f});
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);

    target.draw(text);
}

void DialogBox::next() {
    dialogIndex++;
    currentTextProgressTime = 0;
}

void DialogBox::complete() {
    currentTextProgressTime = maximumTextProgressTime;
}

void DialogBox::startDialog(const std::vector<std::string>& dialog, std::function<void()> callback) {
    dialogIndex = 0;
    this->dialog = dialog;
	this->callback = callback;
    currentTextProgressTime = 0;
    maximumTextProgressTime = 1.0f;

}

bool DialogBox::isInProgress() const {
    return dialogIndex < dialog.size();
}
