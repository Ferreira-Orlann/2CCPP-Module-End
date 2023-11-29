#pragma once

#include "tiles.hpp"
#include <vector>
#include "player.hpp"
#include "layinggrass.hpp"
#include <memory>

namespace LayingGrass {
	class CollisionEngine
	{
	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTileVec = std::vector<LayingGrass::PlacedShapedTile>();
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTileVec = std::vector<LayingGrass::PlacedEffectTile>();
	public:
		CollisionEngine();
		void AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener);
		void AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener);
		bool CollideCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo);
		bool CollideCoordonates(std::vector<LayingGrass::PlacedTile::Coordonates>& vecOne, std::vector<LayingGrass::PlacedTile::Coordonates>& vecTwo);
		bool CanPlaceTile(LayingGrass::PlacedTile& tile);
		bool PlaceShapedTile(LayingGrass::PlacedShapedTile& tile);
		bool PlaceEffectTile(LayingGrass::PlacedEffectTile& tile);
		std::vector<LayingGrass::PlacedShapedTile>::iterator ShapedTilesBegin();
		std::vector<LayingGrass::PlacedShapedTile>::iterator ShapedTilesEnd();
		std::vector<LayingGrass::PlacedEffectTile>::iterator EffectTilesBegin();
		std::vector<LayingGrass::PlacedEffectTile>::iterator EffectTilesEnd();

	};
} 