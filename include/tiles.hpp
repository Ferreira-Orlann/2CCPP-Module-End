#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "player.hpp"

#define SHAPE_COUNT 96
#define SHAPE_HEIGHT 7
#define SHAPE_MATRIX_SIZE (SHAPE_HEIGHT*SHAPE_HEIGHT)
#define TILE_COUNT (SHAPE_COUNT*SHAPE_MATRIX_SIZE)

namespace LayingGrass
{
	// Represent a shape
	// Only computing, doesn't have any graphic elements
	
	const std::bitset<TILE_COUNT> shapesData = {}; // Memory Usage => 2400 bits => 304 octets
	
	class ShapedTile
	{
	private:
		// std::bitset's memory size => nombre de bits * 8, que l'on arrondi au multiple de 4 inférieur, auquel on ajoite 4 (word size)
		std::bitset<SHAPE_MATRIX_SIZE> shapeBits = {}; // Memory Usage => 4 octed | 384 pour 96 Tiles  
		// Total Memory => 784 octets pour 9 joueurs
		short offset;
	public:
		ShapedTile(uint8_t offset);
	protected:
		std::bitset<SHAPE_MATRIX_SIZE> GetShapeMatrix();
	private:
		std::bitset<SHAPE_MATRIX_SIZE> CreateShapeMatrix();
	};

	class EffectTile
	{
	public:
		enum EffectTileType : uint8_t
		{
			COUPON,
			STONE,
			ROBBERY
		};
	private:
		EffectTileType type;
	public:
		EffectTile::EffectTileType GetType();
	};

	// x & y => start at 0
	class PlacedTile
	{
	public:
		struct Coordonates
		{
			uint8_t x;
			uint8_t y;	
		};
	protected:
		Coordonates coordonates;
	public:
		LayingGrass::PlacedTile::Coordonates GetCenterCoordonate();
		virtual void BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener);
		virtual PlayerId GetOwner();
	};

	class PlacedEffectTile : public LayingGrass::PlacedTile, public LayingGrass::EffectTile {};

	class PlacedShapedTile : public LayingGrass::PlacedTile, public LayingGrass::ShapedTile
	{
	public:
		enum Orientation : uint8_t
		{
			TOP,
			DOWN,
			RIGHT,
			LEFT
		};
	private:
		PlayerId pid;
		PlacedShapedTile::Orientation orientation;
	public:
		virtual void BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener);
		virtual PlayerId GetOwner();
	};
}