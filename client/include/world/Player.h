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

    float last_delta = 0.0f;

    bool lockMovement = false;

    sf::Shader* playerShader = nullptr;
    mutable float hit_animation_current = 0.0f;
    mutable bool hit_animation_is_playing = false;
    static constexpr float hit_animation_max = 3.1415926f / 2.0f;

	mutable sf::Sprite sprite;
	std::map<Direction, sf::Texture*> textureMap;

	std::chrono::system_clock::time_point lastInteract = std::chrono::system_clock::now() - std::chrono::milliseconds(1000),
		lastCollision = std::chrono::system_clock::now() - std::chrono::milliseconds(1000);
	sf::Sound interactSound, noInteractSound, collisionSound, walkSound, heartBeatSound;

    float heartBeatDelay = 2000.0f;
    float timeSinceLastHeartBeat = 0;
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

	void teleport(sf::Vector2i position);

    void setHeartBeatDelay(float delay);

    float getHeartBeatDelay();

	void animateHit();
};


#endif //LD51_CLIENT_PLAYER_H
