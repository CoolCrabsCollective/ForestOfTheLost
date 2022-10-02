//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_PLAYER_H
#define LD51_CLIENT_PLAYER_H

#include <map>
#include "Entity.h"
#include "world/Direction.h"
#include <optional>
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Alive.h"
#include "Solid.h"
#include <chrono>
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"
#include "world/anime/Anime.h"

class Player : public Entity, public Alive<int>, public Solid, public Anime {
    sf::Vector2f renderPosition = {};

    Direction currentDir;
    Direction destinationDir;

    std::optional<Direction> inputDir;

    float actionProgress = 0;

    const float movingSpeed = 3.0;
    const float rotationSpeed = 25.0;

    bool lockMovement = false;

	mutable sf::Sprite sprite;
	std::map<Direction, sf::Texture*> textureMap;

	std::chrono::system_clock::time_point lastInteract = std::chrono::system_clock::now() - std::chrono::milliseconds(1000),
		lastCollision = std::chrono::system_clock::now() - std::chrono::milliseconds(1000);
	sf::Sound interactSound, noInteractSound, collisionSound;
public:
	Player(World& world);

    sf::Vector2f getRenderPosition() const override;

	void move(std::optional<Direction> direction);
	void interact();

    void tick(float delta) override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    bool isBlocking(sf::Vector2i vec) override;

	int getZOrder() const override;

    bool isLockMovement() const;

    void setLockMovement(bool lockMovement);
};


#endif //LD51_CLIENT_PLAYER_H
