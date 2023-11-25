#include "collision.hpp"

void LayingGrass::CollisionEngine::AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile::Coordonates> contener)
{
}

void LayingGrass::CollisionEngine::AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile::Coordonates> contener)
{
}

void LayingGrass::CollisionEngine::CollideTiles(std::vector<LayingGrass::PlacedTile::Coordonates>& tOne, std::vector<LayingGrass::PlacedTile::Coordonates>& tTwo)
{
}

bool LayingGrass::CollisionEngine::CanPlaceTile(LayingGrass::PlacedTile& tile)
{
	for (auto tile : this->placedEffectTileVec)
	{

	}
	return false;
}

bool LayingGrass::CollisionEngine::PlaceShapedTile(LayingGrass::PlacedShapedTile& tile)
{
	if (this->CanPlaceTile(tile))
	{
		this->placedShapedTileVec.push_back(tile);
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::PlaceEffectTile(LayingGrass::PlacedEffectTile& tile)
{
	if (this->CanPlaceTile(tile))
	{
		this->placedEffectTileVec.push_back(tile);
		return true;
	}
	return false;
}
