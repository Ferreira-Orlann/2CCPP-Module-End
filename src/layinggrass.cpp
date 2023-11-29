#include "layinggrass.hpp"

template <class T>
bool LayingGrass::LayingGrassInstance<T>::RegisterPlayer(std::shared_ptr<T> player)
{
	if (this->pPlayerVec.size() == this->pPlayerVec.capacity())
	{
		this->Start();
		return false;
	}
	this->pPlayerVec.push_back(player);
	return true;
}

template <class T>
LayingGrass::ShapedTile LayingGrass::LayingGrassInstance<T>::BuildNextShapedTile() const
{
	return NULL;
}

template <class T>
bool LayingGrass::LayingGrassInstance<T>::RockPlace(uint8_t x, uint8_t y)
{

	return true; 
}

template <class T>
void LayingGrass::LayingGrassInstance<T>::Start()
{
	this->pPlayerVec.shrink_to_fit();
	this->gameState = WAITING_SHAPED_TILE_PLACE;
}

template <class T>
LayingGrass::LayingGrassGameState LayingGrass::LayingGrassInstance<T>::GetGameState()
{
	return this->gameState;
}