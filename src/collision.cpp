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

void LayingGrass::CollisionEngine::AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedShapedTile>& contener)
{
	for (auto tile : this->placedShapedTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (tcoordonate == origin)
			continue;
		if (std::abs(origin.x - tcoordonate.x) < (SHAPE_HEIGHT + 1) || std::abs(origin.y - tcoordonate.y) < (SHAPE_HEIGHT + 1))
			contener.push_back(tile);
	}
}

void LayingGrass::CollisionEngine::AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedEffectTile>& contener)
{
	for (auto tile : this->placedEffectTileVec)
	{
		LayingGrass::PlacedTile::Coordonates tcoordonate = tile.GetCenterCoordonate();
		if (tcoordonate.x == origin.x && tcoordonate.y == origin.y)
			continue;
		if (std::abs(origin.x - tcoordonate.x) < (SHAPE_HEIGHT + 1) || std::abs(origin.y - tcoordonate.y) < (SHAPE_HEIGHT + 1))
			contener.push_back(tile);
	}
}

bool LayingGrass::CollisionEngine::CollideCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo)
{
	fprintf(stdout, "Collide: %d, %d\nPos: %d, %d --- , %d\n", std::abs(cOne.x - cTwo.x) == 1, std::abs(cOne.y - cTwo.y) == 1, cOne.x, cOne.y, (std::abs(cOne.x - cTwo.x) == 1) && (std::abs(cOne.y - cTwo.y) == 1));
	if ((std::abs(cOne.x - cTwo.x) == 1	) != (std::abs(cOne.y - cTwo.y) == 1))
	{
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::JuxCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo)
{
	if (cOne.x == cTwo.x && cOne.y == cTwo.y)
	{
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::CanPlaceTile(LayingGrass::PlacedTile& tile, bool bypass)
{
	fprintf(stdout, "CAN PLACE %d\n", bypass);

	PlayerId callerPid = tile.GetOwner();
	std::vector<LayingGrass::PlacedShapedTile> contenerShaped;
	std::vector<LayingGrass::PlacedEffectTile> contenerEffect;
	LayingGrass::PlacedTile::Coordonates origin = tile.GetCenterCoordonate();
	this->AdjacentShapedTiles(origin, contenerShaped);
	this->AdjacentEffectTiles(origin, contenerEffect);
	std::vector<LayingGrass::PlacedTile::Coordonates> tileCoorVec;
	tile.BuildCoordonatesVector(tileCoorVec);
	bool territoryCollide = bypass;
	// A refactoriser
	for (auto target : contenerShaped)
	{
		std::vector<LayingGrass::PlacedTile::Coordonates> targetCoorVec;
		target.BuildCoordonatesVector(targetCoorVec);

		for (auto coorOne : tileCoorVec)
		{
			for (auto coorTwo : targetCoorVec)
			{
				if (callerPid == target.GetOwner())
					if (this->CollideCoordonate(coorOne, coorTwo))
					{
						fprintf(stdout, "TERRITORY\n");

						territoryCollide = true;
					}
				if (this->JuxCoordonate(coorOne, coorTwo))
				{
					return false;
				}
			}
		}
	}
	for (auto target : contenerEffect)
	{
		std::vector<LayingGrass::PlacedTile::Coordonates> targetCoorVec;
		target.BuildCoordonatesVector(targetCoorVec);

		for (auto coorOne : tileCoorVec)
		{
			for (auto coorTwo : targetCoorVec)
			{
				if (this->JuxCoordonate(coorOne, coorTwo))
				{
					return false;
				}
			}
		}
	}
	fprintf(stdout, "CAN PLACE %d\n", territoryCollide);
	return territoryCollide;
}

bool LayingGrass::CollisionEngine::PlaceShapedTile(LayingGrass::PlacedShapedTile tile, bool bypass)
{
	if (this->CanPlaceTile(tile, bypass))
	{
		this->placedShapedTileVec.push_back(tile);
		return true;
	}
	return false;
}

bool LayingGrass::CollisionEngine::PlaceEffectTile(LayingGrass::PlacedEffectTile tile)
{
	if (this->CanPlaceTile(tile, false))
	{
		this->placedEffectTileVec.push_back(tile);
		// A Faire => Effect Detection (switch)
		return true;
	}
	return false;
}

LayingGrass::PlacedEffectTile& LayingGrass::CollisionEngine::GetPlacedShapedTile(LayingGrass::PlacedTile::Coordonates coordonate)
{
	for (auto target : this->placedShapedTileVec)
	{
		std::vector<LayingGrass::PlacedTile::Coordonates> targetCoorVec;
		target.BuildCoordonatesVector(targetCoorVec);
	}
}

LayingGrass::PlacedEffectTile& LayingGrass::CollisionEngine::GetPlacedEffectTile(LayingGrass::PlacedTile::Coordonates coordonate)
{

}