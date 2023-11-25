#include "layinggrass.hpp"

using namespace LayingGrass;

LayingGrassInstance::LayingGrassInstance(uint8_t nbPlayer)
{
	this->pPlayerVec.reserve(nbPlayer);
}

bool LayingGrass::LayingGrassInstance::RegisterPlayer(LayingGrass::pPlayer player)
{
	if (this->pPlayerVec.size() == this->pPlayerVec.capacity())
		return false;
	this->pPlayerVec.push_back(player);
	return true;
}

LayingGrass::ShapedTile LayingGrass::LayingGrassInstance::BuildNextShapedTile() const
{
	return NULL;
}

bool LayingGrass::LayingGrassInstance::RockPlace(uint8_t x, uint8_t y)
{

	return true; 
}
