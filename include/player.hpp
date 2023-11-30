#pragma once

#include <memory>

#define PLAYER_MAX 9
#define PLAYER_MIN 2
#define PLAYER_NONE UINT8_MAX;

#include "raylib.h"

namespace LayingGrass
{
	typedef uint8_t PlayerId;

	class Player
	{	
	private:
		PlayerId id;
		uint8_t coupons;
		size_t territorySize;
	protected:
		void SetPlayerId(LayingGrass::PlayerId id);
	public:
		void IncrementTerritorySize();
		void DecrementTerritorySize();
		void IncrementCoupons();
		void DecrementCoupons();
		PlayerId GetPlayerId();
	};
	typedef std::shared_ptr<Player> pPlayer;

	class VisualPlayer : Player
	{
	private:
		Color color;
	public:
		VisualPlayer(Color c, PlayerId id);
		Color GetColor();
	};
}
