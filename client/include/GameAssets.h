//
// Created by Alexander Winter on 2022-02-13.
//

#ifndef GAMETEMPLATE_GAMEASSETS_H
#define GAMETEMPLATE_GAMEASSETS_H

#include "ShaderAsset.h"
#include "WIZ/asset/MusicAsset.h"
#include "WIZ/asset/SoundAsset.h"
#include "WIZ/asset/FontAsset.h"
#include "WIZ/asset/TextureAsset.h"

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	ASSET(wiz::MusicAsset, GREENLIFE, ("music/greenlife.ogg"))
	ASSET(wiz::SoundAsset, JUMP, ("sfx/jump.ogg"))
	ASSET(wiz::FontAsset, SANS_TTF, ("font/sans.ttf"))

	ASSET(wiz::TextureAsset, PLAYER, ("gfx/player.png"))
	ASSET(wiz::TextureAsset, BACKGROUND, ("gfx/background.jpg"))
	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))
	ASSET(wiz::TextureAsset, LOGO, ("gfx/logo.png"))

	ASSET(ShaderAsset, SPOOKY_SHADER, ("shaders/spooky.vs", "shaders/spooky.fs"))

	ASSET(wiz::TextureAsset, GRASS_TERRAIN, ("gfx/terrain/grass.png"))
	ASSET(wiz::TextureAsset, WATER_TERRAIN, ("gfx/terrain/water.png"))
	ASSET(wiz::TextureAsset, SAND_TERRAIN, ("gfx/terrain/sand.png"))
}


#endif //GAMETEMPLATE_GAMEASSETS_H
