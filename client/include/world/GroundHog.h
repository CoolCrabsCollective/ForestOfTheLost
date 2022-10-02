//
// Created by cedric on 2022-10-02.
//

#ifndef LD51_CLIENT_GROUNDHOG_H
#define LD51_CLIENT_GROUNDHOG_H

#include "Monster.h"

class GroundHog : public Monster {
public:
    explicit GroundHog(World &world, sf::Vector2i position);

    void drawDarkness(sf::RenderTarget &target, sf::Shader *shader) const override;

protected:
};



#endif //LD51_CLIENT_GROUNDHOG_H
