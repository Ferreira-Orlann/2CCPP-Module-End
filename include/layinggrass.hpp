#pragma once

#include <vector>

#include "player.hpp"
#include "board.hpp"
#include "tile.hpp"

namespace LayingGrass
{
	class LayingGrassClass
	{
	private:
			std::vector<upShapedTile> shapedTiles;
			char tileCounter;
			std::vector<pPlayer> pPlayers;
			std::vector<PlacedShapedTile> placedTiles;
	
			enum {
				WAITING_FOR_PLACE;
			};
	public:
		void RegisterPlayer(pPlayer player);
		void PlaceNextTile(pPlayer pplayer, uint8_t x, uint8_t y, PlacedShapedTile::Orientation orientation);
		union {
			std::bitset<25>[5];
			NULL;
		} ExchangeCoupon();
		std::bitset<25> GetNextTileMatrix() const;
		auto PlacedTilesIterateBegin() const;
		auto PlacedTilesIterateEnd() const;
	};
}