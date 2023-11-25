#include "collision.hpp"
#include <cstdlib>

void LayingGrass::CollisionEngine::AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener)
{
	for (auto tile : this->placedShapedTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (std::abs(origin.x - tcoordonate.x) < 6 || std::abs(origin.y - tcoordonate.y) < 6)
			contener.push_back(tile);
	}
}

void LayingGrass::CollisionEngine::AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener)
{
	for (auto tile : this->placedEffectTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (std::abs(origin.x - tcoordonate.x) < 6 || std::abs(origin.y - tcoordonate.y) < 6)
			contener.push_back(tile);
	}
}

bool LayingGrass::CollisionEngine::CollideCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo)
{
	if (std::abs(cOne.x - cTwo.x) > 0 || std::abs(cOne.y - cTwo.y) > 0)
	{
		return true;
	}
	return false;

}

bool LayingGrass::CollisionEngine::CollideCoordonates(std::vector<LayingGrass::PlacedTile::Coordonates>& vecOne, std::vector<LayingGrass::PlacedTile::Coordonates>& vecTwo)
{
	for (auto coorOne : vecOne)
	{
		for (auto coorTwo : vecTwo)
		{
			if (this->CollideCoordonate(coorOne, coorTwo))
				return true;
		}
	}
	return false;
}

bool LayingGrass::CollisionEngine::CanPlaceTile(LayingGrass::PlacedTile& tile, PlayerId pid)
{
	std::vector<LayingGrass::PlacedTile> contener;
	LayingGrass::PlacedTile::Coordonates origin = tile.GetCenterCoordonate();
	this->AdjacentEffectTiles(origin, contener);
	this->AdjacentShapedTiles(origin, contener);
	std::vector<LayingGrass::PlacedTile::Coordonates> tileCoorVec;
	tile.BuildCoordonatesVector(tileCoorVec);
	for (auto target : contener)
	{
		std::vector<LayingGrass::PlacedTile::Coordonates> targetCoorVec;
		target.BuildCoordonatesVector(targetCoorVec);
		if (this->CollideCoordonates(tileCoorVec, targetCoorVec))
		{

		}
	
	}

	return false;
}

bool LayingGrass::CollisionEngine::PlaceShapedTile(LayingGrass::PlacedShapedTile& tile)
{
	if (this->CanPlaceTile(tile, tile.GetPlayerId()))
	{
		this->placedShapedTileVec.push_back(tile);
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::PlaceEffectTile(LayingGrass::PlacedEffectTile& tile)
{
	if (this->CanPlaceTile(tile, PLAYER_NONE))
	{
		this->placedEffectTileVec.push_back(tile);
		return true;
	}
	return false;
}
