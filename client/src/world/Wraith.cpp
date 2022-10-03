//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Wraith.h"

Wraith::Wraith(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::INVISIBLE), world.getAssets().get(GameAssets::WRAITH)){
    attackMessage = "Cold. Why am I so cold? A piercing scream fills your ears. Your own. A wraith has killed you.";
    scaleDark = 3.0f;
    scale = 3.0f;
}

void Wraith::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	//if (position == destination)
	//	return;

	daySprite.setPosition({renderPosition.x - scale / 4.0f, -renderPosition.y - scale / 4.0f});
	daySprite.setScale({ scale / daySprite.getTexture()->getSize().x, scale / daySprite.getTexture()->getSize().y });

	if(destination.x > position.x)
		daySprite.setScale(sf::Vector2f { -1.0f * daySprite.getScale().x, 1.0f * daySprite.getScale().y });

	target.draw(daySprite);
}

void Wraith::drawDarkness(sf::RenderTarget &target) const {
	if(this->getWorld().getPhase() > GamePhase::INITIAL)
	{
		nightSprite.setPosition({renderPosition.x - scaleDark / 4.0f, -renderPosition.y - scaleDark / 4.0f});
		nightSprite.setScale({ scaleDark / nightSprite.getTexture()->getSize().x, scaleDark / nightSprite.getTexture()->getSize().y });

		if(destination.x > position.x)
			nightSprite.setScale(sf::Vector2f { -1.0f * nightSprite.getScale().x, 1.0f * nightSprite.getScale().y });
		target.draw(nightSprite);
	}
}
