//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_BUSH_H
#define LD51_CLIENT_BUSH_H


#include "HidingSpot.h"

enum BushType {
    BUSH = 0,
    BUSH2,
    WITHERED_BUSH,
    WITHERED_BUSH2
};

class Bush : public HidingSpot, public Interactable {
public:
	Bush(World& world, const sf::Vector2i& position, BushType bushType);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void shake() override;

    void tick(float delta) override;

	bool activate() override;

protected:
    sf::Vector2f bush_shake_scale = { 1.0f, 1.0f };
    sf::Vector2f bush_shake_intensity { 0.2f, 0.05f };
    float bush_delta = 0.0f;
    float bush_shake_time = 500.f;
    float bush_shake_speed = 30.0f;
    bool bush_is_shaking = false;

    BushType bush_type;
};


#endif //LD51_CLIENT_BUSH_H
