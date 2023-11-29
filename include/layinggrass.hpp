#pragma once

#include <vector>
#include <memory>

#include "collision.hpp"
#include "player.hpp"
#include "tiles.hpp"

#define SHAPED_TILE_PER_PLAYER 10.67

namespace LayingGrass {
	// De base il avais son propre header mais à cause du compilater j'ai été obligé de transféré içi
	class CollisionEngine
	{
	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTileVec = std::vector<LayingGrass::PlacedShapedTile>();
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTileVec = std::vector<LayingGrass::PlacedEffectTile>();
	public:
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

	enum LayingGrassGameState : uint8_t {
		WAITING_FOR_PLAYERS,
		WAITING_SHAPED_TILE_PLACE,
		WAITING_ROCK_PLACE,
		WAITING_ROBBERY_SELECT,
		WAITING_ROBBERY_PLACE,
		WAITING_EXHANGED_SHAPED_TILE_SELECT,
		END
	};

	template <typename T>
	class LayingGrassInstance
	{
	private:
		uint8_t tileCounter = 0;
		std::vector<std::shared_ptr<T>> pPlayerVec = std::vector<std::shared_ptr<T>>();
		LayingGrass::PlayerId cpid = -1;
		LayingGrassGameState gameState = WAITING_SHAPED_TILE_PLACE;
		LayingGrass::CollisionEngine engine;
	public:
		LayingGrassInstance();
		bool RegisterPlayer(std::shared_ptr<T> player);
		bool PlaceTile(LayingGrass::ShapedTile shapedTile, uint8_t x, uint8_t y, LayingGrass::PlacedShapedTile::Orientation orientation);
		LayingGrass::ShapedTile BuildNextShapedTile() const;
		struct {
			LayingGrass::ShapedTile data[5];
		} BuildExchangeShapedTile();
		bool RockPlace(uint8_t x, uint8_t y);
		void Start();
;		bool ExchangeCoupon();
		auto PlacedTilesIterateBegin() const;
		auto PlacedTilesIterateEnd() const;	
		std::shared_ptr<T> GetPlayer();
		LayingGrass::LayingGrassGameState GetGameState();
		std::unique_ptr<LayingGrass::CollisionEngine> GetEngine();
		size_t GetPlayerCount();
	};


	// Obligé de faire les template dans un .hpp ou .h
	template <typename T>
	LayingGrass::LayingGrassInstance<T>::LayingGrassInstance()
	{
		this->pPlayerVec.reserve(9);
	}

	template <typename  T>
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

	template <typename T>
	LayingGrass::ShapedTile LayingGrass::LayingGrassInstance<T>::BuildNextShapedTile() const
	{
		return NULL;
	}

	template <typename  T>
	bool LayingGrass::LayingGrassInstance<T>::RockPlace(uint8_t x, uint8_t y)
	{

		return true;
	}

	template <typename  T>
	void LayingGrass::LayingGrassInstance<T>::Start()
	{
		this->pPlayerVec.shrink_to_fit();
		this->gameState = WAITING_SHAPED_TILE_PLACE;
	}

	template <typename  T>
	LayingGrass::LayingGrassGameState LayingGrass::LayingGrassInstance<T>::GetGameState()
	{
		return this->gameState;
	}

	template <typename  T>
	std::unique_ptr<LayingGrass::CollisionEngine> LayingGrass::LayingGrassInstance<T>::GetEngine()
	{
		return std::make_unique<LayingGrass::CollisionEngine>(this->engine);
	}

	template <typename  T>
	size_t LayingGrass::LayingGrassInstance<T>::GetPlayerCount()
	{
		return this->pPlayerVec.size();
	}
	////////////////////////////////////////////////////////////////////////////////////
}