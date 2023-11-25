#pragma once

#include <vector>
#include <memory>

#include "player.hpp"
#include "tiles.hpp"
#include "collision.hpp"

#define SHAPED_TILE_PER_PLAYER 10.67

namespace LayingGrass {

	enum LayingGrassGameState : uint8_t {
		WAITING_FOR_PLAYER,
		WAITING_SHAPED_TILE_PLACE,
		WAITING_ROCK_PLACE,
		WAITING_ROBBERY_SELECT,
		WAITING_ROBBERY_PLACE,
		WAITING_EXHANGED_SHAPED_TILE_SELECT,
		END
	};

	class LayingGrassInstance
	{
	private:
		uint8_t tileCounter = 0;
		std::vector<LayingGrass::pPlayer> pPlayerVec = std::vector<LayingGrass::pPlayer>();
		LayingGrass::PlayerId cpid = -1;
		LayingGrass::CollisionEngine engine = LayingGrass::CollisionEngine();
	public:
		LayingGrassInstance(uint8_t playerNb);
		bool RegisterPlayer(LayingGrass::pPlayer player);
		bool PlaceTile(LayingGrass::ShapedTile shapedTile, uint8_t x, uint8_t y, LayingGrass::PlacedShapedTile::Orientation orientation);
		LayingGrass::ShapedTile BuildNextShapedTile() const;
		struct {
			LayingGrass::ShapedTile data[5];
		} BuildExchangeShapedTile();
		bool RockPlace(uint8_t x, uint8_t y);
;		bool ExchangeCoupon();
		auto PlacedTilesIterateBegin() const;
		auto PlacedTilesIterateEnd() const;
		LayingGrass::pPlayer GetPlayer();
	};

}