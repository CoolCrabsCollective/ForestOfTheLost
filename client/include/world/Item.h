//
// Created by cedric on 2022-10-01.
//

#ifndef LD51_CLIENT_ITEM_H
#define LD51_CLIENT_ITEM_H

#include <utility>

#include "World.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"

class Item : public Entity, public Solid {
public:
    explicit Item(World& world, sf::Texture* texture, sf::Vector2i position);

    bool isBlocking(sf::Vector2i vec) override;

    void tick(float delta) override;

protected:
    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
    mutable sf::Sprite sprite;
};

#endif //LD51_CLIENT_ITEM_H
