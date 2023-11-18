#pragma once

#include <memory>

#define PLAYER_MAX 9
#define PLAYER_MIN 2

namespace LayingGrass
{
	typedef uint8_t PlayerId;
	class Player
	{
	private:
		PlayerId id;
		uint8_t coupons;
		size_t territorySize;
	public:
		void IncrementTerritorySize();
		void DecrementTerritorySize();
		void IncrementCoupons();
		void DecrementCoupons();
		PlayerId GetPlayerId();
	};
	typedef std::shared_ptr<Player> pPlayer;
}
