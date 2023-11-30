#pragma once

#include <vector>
#include <memory>

#include "collision.hpp"
#include "player.hpp"
#include "tiles.hpp"

#include <cmath>
#include <random>

#define SHAPED_TILE_PER_PLAYER 10.67

namespace LayingGrass {
	// De base il avais son propre header mais à cause du compilater j'ai été obligé de transféré içi
	class CollisionEngine
	{
	public:
		struct ShapedGetterResult
		{
			bool result;
			PlacedShapedTile data;
		};

		struct EffectGetterResult
		{
			bool result;
			PlacedEffectTile data;
		};

	private:
		std::vector<LayingGrass::PlacedShapedTile> placedShapedTileVec = std::vector<LayingGrass::PlacedShapedTile>();
		std::vector<LayingGrass::PlacedEffectTile> placedEffectTileVec = std::vector<LayingGrass::PlacedEffectTile>();
		size_t boardSize;
	public:
		void AdjacentShapedTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedShapedTile>& contener);
		void AdjacentEffectTiles(LayingGrass::PlacedTile::Coordonates origin, std::vector<LayingGrass::PlacedEffectTile>& contener);
		bool CollideCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo);
		bool JuxCoordonate(LayingGrass::PlacedTile::Coordonates cOne, LayingGrass::PlacedTile::Coordonates cTwo);
		bool CanPlaceTile(LayingGrass::PlacedTile& tile, bool bypass);
		bool PlaceShapedTile(LayingGrass::PlacedShapedTile tile, bool bypass);
		bool PlaceEffectTile(LayingGrass::PlacedEffectTile tile);
		std::vector<LayingGrass::PlacedShapedTile>::iterator ShapedTilesBegin();
		std::vector<LayingGrass::PlacedShapedTile>::iterator ShapedTilesEnd();
		std::vector<LayingGrass::PlacedEffectTile>::iterator EffectTilesBegin();
		std::vector<LayingGrass::PlacedEffectTile>::iterator EffectTilesEnd();
		std::vector<LayingGrass::PlacedShapedTile>& GetPlacedShapedTileVector();
		std::vector<LayingGrass::PlacedEffectTile>& GetPlacedEffectTileVector();
		ShapedGetterResult GetPlacedShapedTile(LayingGrass::PlacedTile::Coordonates coordonate);
		EffectGetterResult GetPlacedEffectTile(LayingGrass::PlacedTile::Coordonates coordonate);
		void DeteteAt(LayingGrass::PlacedTile::Coordonates center);
		size_t GetBoardSize();
		void SetBoardSize(size_t size);
	};

	enum LayingGrassGameState : uint8_t {
		WAITING_FOR_PLAYERS,
		TERRITORY,
		WAITING_SHAPED_TILE_PLACE,
		WAITING_ROCK_PLACE,
		WAITING_ROCK_SELECT,
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
		LayingGrassGameState gameState = WAITING_FOR_PLAYERS;
		LayingGrass::CollisionEngine engine;
		uint8_t round = 0;
		std::vector<size_t> skippedTiles = std::vector<size_t>();
	protected:
		void SetGameState(LayingGrass::LayingGrassGameState state);
		LayingGrass::PlacedShapedTile::Orientation orientation = LayingGrass::PlacedShapedTile::Orientation::TOP;
	public:
		LayingGrassInstance();
		bool RegisterPlayer(std::shared_ptr<T> player);
		void PlaceTile(LayingGrass::PlacedTile::Coordonates coordonate, LayingGrass::PlacedShapedTile::Orientation orientation);
		bool PlaceTileEx(LayingGrass::PlacedTile::Coordonates coordonate, LayingGrass::PlacedShapedTile::Orientation orientation, uint8_t offset);
		LayingGrass::PlacedShapedTile BuildNextShapedTile();
		struct {
			LayingGrass::ShapedTile data[5];
		} BuildExchangeShapedTile();
		bool RockPlace(uint8_t x, uint8_t y);
		void Start();
;		bool ExchangeCoupon();
		std::shared_ptr<T> GetPlayer(PlayerId id);
		LayingGrass::LayingGrassGameState GetGameState();
		LayingGrass::CollisionEngine& GetEngine();
		size_t GetPlayerCount();
		void PlayerActionEnd();
		size_t GetBoardSize();
		uint8_t GetTileCounter();
	};

	// Obligé de faire les template dans un .hpp ou .h
	template <typename T>
	uint8_t LayingGrass::LayingGrassInstance<T>::GetTileCounter()
	{
		if (this->tileCounter < std::ceil(this->GetPlayerCount() * 10.67))
		{
			return this->tileCounter;
		} 
		return this->skippedTiles.front();
	}

	template <typename T>
	size_t LayingGrass::LayingGrassInstance<T>::GetBoardSize(){
		if (this->GetPlayerCount() < 5)
		{
			return 20;
		}
		return 30;
	};

	template <typename T>
	LayingGrass::LayingGrassInstance<T>::LayingGrassInstance()
	{
		this->engine.SetBoardSize(this->GetBoardSize());
		this->pPlayerVec.reserve(9);
		std::string str = "0000000000000000000000001100000000000000000000000000000000000000010000001110000000000000000000000000000000001000000100000111000000000000000000000000000000000000000010000011100000100000000000000000000000000000000000100001110000100000000000000000000000000000000000110000011000000000000000000000000000000000000000101000011100000000000000000000000000000000000000000000001110000000000000000000000000000000000000000100000110000010000000000000000000000000000000000100000011000000000000000000000000000000000000000000100000110000110000000000000000000000000000000000000000011000000000000000000000000000000000010000011000001000000100000011000000000000000000011100001000000100000010000001000000000000000000000100000010000001100011100011000000000000000000000000000001000001100001100000100000000000000000000000000001000001110000110000000000000000000000000000000000000000111000000000000000000000000000000000000000010000001100000100000010000000000000000000000000000110000110000011000000000000000000000000000000000100000110000011100000000000000000000000000100000010000011100001000000000000000000000000000000000010000001100000000000000000000000000000000000000000110000011000001100000000000000000000000001110000010000001000000100000000000000000000000000100000011000000110000001100000000000000000000000000000000000001111100000000000000000000000000000000000000100000011100000010000001000000000000000000010000001100000100000011000001000000000000000000000000000100000011000001100000100000000000000000000100000010000001000001110000101000000000000000000000000000000000110000000000000000000000000000000000000001000000111000010110000000000000000000000000010000001000001100000100000010000000000000000000110000001000000111000110000010000000000000000000001000000100000011000001000000000000000000000000000000000001000001100000100000000000000000000000000000000010010001111000000000000000000000000000000000000000011010000101111110000000000000000000000001000000100000011000000111000000000000000000000000110000001100001100000011000001000000000000000000000000000100000011000001100000000000000000000000000000000010000001000001111000000000000000000000000000000001100000110000000000000000000000000000000000000000010000011000001100000100000000000000000000000000111000001000001100000000000000000000000000000000000000001111000000000000000000000000000000000000000100000111000000000000000000000000000000000000001000000100000011110000000000000000000000000000000001100001100000011100000000000000000000000000000000010000011000001000000100000000000000000000000000100000011100000000000000000000000000000000010000001100000100000010000001000000000000000000001110000100000010000001000011100000000000000100000010000011000001000000110000010000000000000000000000000000000001111000000000000000000000000000000000000001100000010000001110000001000000000000000000100000010000011100000100000010000000000000000000010000001000011100000000000000000000000000010000001000000100000010000001000000100000000000000000000000000101000011100000100000110000000000000000000000000001000011100000111000010000000000000000000001100000100000010000011100000000000000000000000000100000010000001100000100000010000000000000000000110000001000000101000111100000000000000000000000001000001100001100000100000011000000000000000000000110000010000001000000100000110000010000000000000000000010100001111000000000000000000000000000000110000001010000101000011100000000000000000000000000100000011000001000000100000010000000000000000001000000101000011110000100000010000000000000011000001000000100000010000001000000100000010000000000000000000010000011100001000000100000000000000000000000000000000000110000000000000000000000000000000000000000010000101000011100000000000000000000000000000000010000011100001010000000000000000000000000010000001000011111000010000001000000000000001000001100000100000010000011000011000000000000000000001100000100000011000001000000110000000000000000000010000001000000100000111100001000000000000000000000100000110000010000001000000100000000000000000000000000011000001000001100000100000000000000110000010000011000000110000010000001000000000000110000011000000110000010000001000000100000000000000000000100000011000011000000100000000000000000000000000000000011000001111000000000000000000000000000000000110001110000100000011000000000000000000000000000110000010000001000001100000000000000000000000000010000001000001110000010000000000000000000000000011100001010000100000011000000000000000000000000000100000011000011000001000000000000000000000000000000000010000001100000111000000000000000000000000001000000100000010000001100000000000000000000000000000000010000011110001000000000000000000000000000000000001100001100000100000010000000000000000000000000000100000110000010000001100000000000000000000000000000000001000000000000000000000000";
		for (int i = 0; i < str.size(); i++)
		{
			char c = str.at(i);
			bool b;
			if (c == '0')
			{
				b = false;
			}
			else
			{
				b = true;
			}
			LayingGrass::GetShapesData()[i] = b;
		}
	}

	template <typename T>
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
	LayingGrass::PlacedShapedTile LayingGrass::LayingGrassInstance<T>::BuildNextShapedTile()
	{
		return LayingGrass::PlacedShapedTile(LayingGrass::PlacedTile::Coordonates(3,3), this->orientation, this->cpid, this->GetTileCounter());
	}

	template <typename T>
	bool LayingGrass::LayingGrassInstance<T>::RockPlace(uint8_t x, uint8_t y)
	{

		return true;
	}

	template <typename T>
	void LayingGrass::LayingGrassInstance<T>::Start()
	{
		this->pPlayerVec.shrink_to_fit();
		this->gameState = TERRITORY;
		this->cpid = 0;

		LayingGrass::CollisionEngine engine = this->GetEngine();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 19);
		for (int i = 0; i < std::ceil(this->GetPlayerCount() * 1.5); i++)
		{
			LayingGrass::PlacedEffectTile tile = LayingGrass::PlacedEffectTile(LayingGrass::PlacedTile::Coordonates(distr(gen), distr(gen)), LayingGrass::EffectTile::EffectTileType::COUPON);
			engine.PlaceEffectTile(tile);
		}
		for (int i = 0; i < std::ceil(this->GetPlayerCount() * 0.5); i++)
		{
			LayingGrass::PlacedEffectTile tile = LayingGrass::PlacedEffectTile(LayingGrass::PlacedTile::Coordonates(distr(gen), distr(gen)), LayingGrass::EffectTile::EffectTileType::STONE);
			engine.PlaceEffectTile(tile);
		}
		for (int i = 0; i < this->GetPlayerCount(); i++)
		{
			LayingGrass::PlacedEffectTile tile = LayingGrass::PlacedEffectTile(LayingGrass::PlacedTile::Coordonates(distr(gen), distr(gen)), LayingGrass::EffectTile::EffectTileType::ROBBERY);
			engine.PlaceEffectTile(tile);
		}
		fprintf(stdout, "Start: %d\n", this->GetEngine().GetPlacedEffectTileVector().size());
	}

	template <typename T>
	LayingGrass::LayingGrassGameState LayingGrass::LayingGrassInstance<T>::GetGameState()
	{
		return this->gameState;
	}

	template <typename T>
	LayingGrass::CollisionEngine& LayingGrass::LayingGrassInstance<T>::GetEngine()
	{
		return this->engine;
	}

	template <typename T>
	size_t LayingGrass::LayingGrassInstance<T>::GetPlayerCount()
	{
		return this->pPlayerVec.size();
	}

	template <typename T>
	std::shared_ptr<T> LayingGrass::LayingGrassInstance<T>::GetPlayer(PlayerId id)
	{
		return this->pPlayerVec[id];
	}

	template <typename T>
	void LayingGrass::LayingGrassInstance<T>::PlaceTile(LayingGrass::PlacedTile::Coordonates coordonate, LayingGrass::PlacedShapedTile::Orientation orientation)
	{
		if (this->PlaceTileEx(coordonate, orientation, this->GetTileCounter()))
		{
			if (this->tileCounter < std::ceil(this->GetPlayerCount() * 10.67))
				this->tileCounter++;
			else
				this->skippedTiles.erase(this->skippedTiles.begin());
		}
	}

	template <typename T>
	bool LayingGrass::LayingGrassInstance<T>::PlaceTileEx(LayingGrass::PlacedTile::Coordonates coordonate, LayingGrass::PlacedShapedTile::Orientation orientation, uint8_t offset)
	{
		auto tile = LayingGrass::PlacedShapedTile(coordonate, orientation, this->cpid, offset);
		bool b = this->GetEngine().PlaceShapedTile(tile, this->gameState == LayingGrass::LayingGrassGameState::TERRITORY);
		// For Debug => bool d = this->GetEngine().PlaceShapedTile(tile, false);
		if (b)
			this->PlayerActionEnd();
		return b;
	}

	template <typename T>
	void LayingGrass::LayingGrassInstance<T>::PlayerActionEnd()
	{
		this->cpid++;
		if (this->cpid == this->GetPlayerCount())
		{
			if (this->gameState == LayingGrass::LayingGrassGameState::TERRITORY)
			{
				this->gameState = LayingGrass::LayingGrassGameState::WAITING_SHAPED_TILE_PLACE;
			}		
			this->cpid = 0;
			this->round++;
			if (this->round == 9)
			{

			}
		}
	}

	template <typename T>
	void LayingGrass::LayingGrassInstance<T>::SetGameState(LayingGrass::LayingGrassGameState state)
	{
		this->gameState = gameState;
	}
	////////////////////////////////////////////////////////////////////////////////////
}