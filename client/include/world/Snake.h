//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_SNAKE_H
#define LD51_CLIENT_SNAKE_H

#include "Monster.h"

class Snake : public Monster {
public:
    explicit Snake(World &world, sf::Vector2i position);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void drawDarkness(sf::RenderTarget &target, sf::Shader *shader) const override;

protected:
};


#endif //LD51_CLIENT_SNAKE_H
