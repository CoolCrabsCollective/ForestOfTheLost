//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_WORLD_H
#define LD51_CLIENT_WORLD_H

#include <vector>
#include <unordered_map>
#include "Terrain.h"
#include "SFML/System/Vector2.hpp"
#include "Player.h"
#include "WIZ/asset/AssetLoader.h"

class Entity;
class Player;

enum GamePhase {
	INITIAL,
	FIRST_ENCOUNTER,
	GHOST,
	MONSTER,
	FINAL
};

struct VecCompare {
	bool operator() (const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
		return lhs.x < rhs.x || lhs.x == rhs.x && lhs.y < rhs.y;
	}
};

class World : public Tickable, public sf::Drawable {
	wiz::AssetLoader& assets;
	std::vector<Entity*> entities;
	Player player;

	std::unordered_map<TerrainType, sf::Texture*> terrain_textures;
	mutable sf::Sprite terrain_sprite;

	std::map<sf::Vector2i, TerrainType, VecCompare> terrainMap;
    std::map<sf::Vector2i, std::vector<Entity*>, VecCompare> entityMap;
    std::vector<Entity*> empty = {};

	mutable std::vector<Entity*> entityDrawList = {};

    bool endPointReached = false;

	float grayscaleness = 0.0f;

	float timeAccumulator = 0.0f;
	float tenSecAccumulator = 0.0f;

	GamePhase currentPhase = INITIAL;
	bool changePhase = false;

public:
	constexpr const static sf::Vector2f VIEW_SIZE = { 24.0f, 13.5f };

	World(wiz::AssetLoader& assets);

	TerrainType getTerrainType(sf::Vector2i position) const;

	const std::vector<Entity*>& getEntities() const;

	const Player& getPlayer() const;

	Player& getPlayer();

	wiz::AssetLoader& getAssets();

    bool tileOccupied(sf::Vector2i tile, Entity *exclude);

    void tick(float delta) override;

    const std::vector<Entity*>& getEntitiesAt(sf::Vector2i position) const;

    void addEntity(Entity* entity);

    void moveEntity(sf::Vector2i oldPosition, Entity* entity);

    bool isEndPointReached() const;

	inline float getGrayscaleness() const {
		return grayscaleness;
	}

	inline float getTimeAccumulator() const {
		return timeAccumulator;
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

private:
	void generatePhase(GamePhase phase);
};


#endif //LD51_CLIENT_WORLD_H
