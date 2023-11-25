#include "tiles.hpp"

using namespace LayingGrass;

LayingGrass::ShapedTile::ShapedTile(uint8_t offset)
{

}

LayingGrass::PlacedTile::Coordonates LayingGrass::PlacedTile::GetCenterCoordonate()
{
	return this->coordonates;
}

void LayingGrass::PlacedTile::BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener)
{
	contener.push_back(this->coordonates);
}

void LayingGrass::PlacedShapedTile::BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener)
{
	contener.push_back(this->coordonates);
}

PlayerId LayingGrass::PlacedShapedTile::GetPlayerId()
{
	return this->pid;
}
