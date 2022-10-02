//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Wraith.h"

Wraith::Wraith(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::INVISIBLE), world.getAssets().get(GameAssets::WRAITH)){
    attackMessage = "Cold. So cold. A piercing scream fills your ears. A wraith has killed you.";
}

void Wraith::drawDarkness(sf::RenderTarget &target, sf::Shader *shader) const {
    nightSprite.setPosition({renderPosition.x, -renderPosition.y});
    nightSprite.setScale({ 4.0f / nightSprite.getTexture()->getSize().x, 4.0f / nightSprite.getTexture()->getSize().y });
    target.draw(nightSprite, shader);
}
