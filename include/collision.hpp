#pragma once

#include "tile.hpp"
#include <vector>

namespace LayingGrass {
	class CollisionEngine
	{
	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTiles;
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTiles;
	public:
		void AdjacentShapedTiles(std::vector<LayingGrass::PlacedEffectTile>& contener);
		void AdjacentEffectTiles(std::vector<LayingGrass::PlacedEffectTile>& contener);
		void CollideShapedTile(LayingGrass::PlacedShapedTile& tOne, LayingGrass::PlacedShapedTile& tTwo);
		void CollideEffectTile(LayingGrass::PlacedShapedTile& tOne, LayingGrass::PlacedEffectTile& tTwo);
		bool CanPlaceTile(LayingGrass::PlacedShapedTile& tile);
		bool PlaceShapedTile(LayingGrass::PlacedShapedTile& tile);
		void PlaceEffectTile(LayingGrass::EffectTile& tile);
	};
}