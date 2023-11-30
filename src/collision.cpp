#include <cstdlib>
#include "layinggrass.hpp"

std::vector<LayingGrass::PlacedShapedTile>::iterator LayingGrass::CollisionEngine::ShapedTilesBegin()
{
	return this->placedShapedTileVec.begin();
}

std::vector<LayingGrass::PlacedShapedTile>::iterator LayingGrass::CollisionEngine::ShapedTilesEnd()
{
	return this->placedShapedTileVec.end();
}

std::vector<LayingGrass::PlacedEffectTile>::iterator LayingGrass::CollisionEngine::EffectTilesBegin()
{
	return this->placedEffectTileVec.begin();
}

std::vector<LayingGrass::PlacedEffectTile>::iterator LayingGrass::CollisionEngine::EffectTilesEnd()
{
	return this->placedEffectTileVec.end();
}

std::vector<LayingGrass::PlacedEffectTile>& LayingGrass::CollisionEngine::GetPlacedEffectTileVector()
{
	return this->placedEffectTileVec;
}

std::vector<LayingGrass::PlacedShapedTile>& LayingGrass::CollisionEngine::GetPlacedShapedTileVector()
{
	return this->placedShapedTileVec;
}


void LayingGrass::CollisionEngine::AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener)
{
	for (auto tile : this->placedShapedTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (std::abs(origin.x - tcoordonate.x) < (SHAPE_HEIGHT + 1) || std::abs(origin.y - tcoordonate.y) < (SHAPE_HEIGHT + 1))
			contener.push_back(tile);
	}
}

void LayingGrass::CollisionEngine::AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedTile> contener)
{
	for (auto tile : this->placedEffectTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (std::abs(origin.x - tcoordonate.x) < (SHAPE_HEIGHT + 1) || std::abs(origin.y - tcoordonate.y) < (SHAPE_HEIGHT + 1))
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

bool LayingGrass::CollisionEngine::CanPlaceTile(LayingGrass::PlacedTile& tile)
{
	PlayerId callerPid = tile.GetOwner();
	std::vector<LayingGrass::PlacedTile> contener;
	LayingGrass::PlacedTile::Coordonates origin = tile.GetCenterCoordonate();
	this->AdjacentEffectTiles(origin, contener);
	this->AdjacentShapedTiles(origin, contener);
	std::vector<LayingGrass::PlacedTile::Coordonates> tileCoorVec;
	tile.BuildCoordonatesVector(tileCoorVec);
	bool territoryCollide = false;
	for (auto target : contener)
	{
		std::vector<LayingGrass::PlacedTile::Coordonates> targetCoorVec;
		target.BuildCoordonatesVector(targetCoorVec);
		if (this->CollideCoordonates(tileCoorVec, targetCoorVec))
		{
			if (callerPid == target.GetOwner())
				territoryCollide = true;
			else
				return false;
		}
	}
	if (!territoryCollide)
		return false;
	return true;
}

bool LayingGrass::CollisionEngine::PlaceShapedTile(LayingGrass::PlacedShapedTile tile, bool bypass)
{
	if (bypass)
	{
		this->placedShapedTileVec.push_back(tile);
		return true;
	}
	if (this->CanPlaceTile(tile))
	{
		this->placedShapedTileVec.push_back(tile);
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::PlaceEffectTile(LayingGrass::PlacedEffectTile tile)
{
	if (this->CanPlaceTile(tile))
	{
		this->placedEffectTileVec.push_back(tile);
		// A Faire => Effect Detection (switch)
		return true;
	}
	return false;
}

