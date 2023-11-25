#pragma once

#include "tiles.hpp"
#include <vector>
#include "player.hpp"

namespace LayingGrass {
	class CollisionEngine
	{
	public:
	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTileVec = std::vector<LayingGrass::PlacedShapedTile>();
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTileVec = std::vector<LayingGrass::PlacedEffectTile>();
	public:
		void AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener);
		void AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener);
		bool CollideCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo);
		bool CollideCoordonates(std::vector<LayingGrass::PlacedTile::Coordonates>& vecOne, std::vector<LayingGrass::PlacedTile::Coordonates>& vecTwo);
		bool CanPlaceTile(LayingGrass::PlacedTile& tile, PlayerId pid);
		bool PlaceShapedTile(LayingGrass::PlacedShapedTile& tile);
		bool PlaceEffectTile(LayingGrass::PlacedEffectTile& tile);
	};
} 