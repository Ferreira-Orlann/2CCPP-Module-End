#pragma once

#include "tiles.hpp"
#include <vector>

namespace LayingGrass {
	class CollisionEngine
	{
	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTileVec = std::vector<LayingGrass::PlacedShapedTile>();
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTileVec = std::vector<LayingGrass::PlacedEffectTile>();
	public:
		void AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile::Coordonates> contener);
		void AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile::Coordonates> contener);
		void CollideTiles(std::vector<LayingGrass::PlacedTile::Coordonates>& tOne, std::vector<LayingGrass::PlacedTile::Coordonates>& tTwo);
		bool CanPlaceTile(LayingGrass::PlacedTile& tile);
		bool PlaceShapedTile(LayingGrass::PlacedShapedTile& tile);
		bool PlaceEffectTile(LayingGrass::PlacedEffectTile& tile);
		std::unique_ptr<std::vector<LayingGrass::PlacedEffectTile>> GetPlacedShapedTileVectorPtr();
		std::unique_ptr<std::vector<LayingGrass::PlacedEffectTile>> GetPlacedEffectTileVectorPtr();
	};
}