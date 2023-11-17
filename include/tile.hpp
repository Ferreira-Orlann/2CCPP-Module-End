#pragma once

#include <bitset>
#include <memory>
#include "player.hpp"

#define SHAPE_COUNT 96
#define SHAPE_MATRIX_SIZE (5*5)
#define TILE_COUNT (SHAPE_COUNT*SHAPE_MATRIX_SIZE)

namespace LayingGrass
{
	// Represent a shape
	// Only computing, doesn't have any graphic elements
	class ShapedTile
	{
	private:
		// std::bitset's memory size => nombre de bits * 8, que l'on arrondi au multiple de 4 inférieur, auquel on ajoite 4 (word size)
		std::bitset<SHAPE_MATRIX_SIZE> shapeBits; // Memory Usage => 4 octed | 384 pour 96 Tiles  
		static const std::bitset<TILE_COUNT> shapesData; // Memory Usage => 2400 bits => 304 octets
		// Total Memory => 784 octets
		short offset;
	public:
		ShapedTile(uint8_t offset);
		std::bitset<SHAPE_MATRIX_SIZE> CreateShapeMatrix();
	};

	class EffecTile
	{
	protected:
		virtual void PlayEffect() = 0;
	};

	class CouponEffectTile : public EffecTile
	{
		virtual void PlayEffect();
	};


	class StoneEffectTile : public EffecTile
	{
		virtual void PlayEffect();
	};

	class RobberyEffectTile : public EffecTile
	{
		virtual void PlayEffect();
	};

	typedef std::unique_ptr<ShapedTile> upShapedTile;

	// x & y => start at 0
	struct PlacedShapedTile
	{
		enum Orientation : uint8_t
		{
			TOP,
			DOWN,
			RIGHT,
			LIFT
		};
		upShapedTile tile;
		uint8_t x;
		uint8_t y;
		PlayerId pid;
		Orientation orientation;
	};
}