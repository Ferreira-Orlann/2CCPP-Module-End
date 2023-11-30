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
	
	class ShapedTile
	{
	private:
		// std::bitset's memory size => nombre de bits * 8, que l'on arrondi au multiple de 4 inférieur, auquel on ajoite 4 (word size)
		std::bitset<SHAPE_MATRIX_SIZE> shapeBits = {}; // Memory Usage => 4 octed | 384 pour 96 Tiles  
		// Total Memory => 784 octets pour 9 joueurs
		uint8_t offset;
	public:
		ShapedTile(uint8_t offset);
	protected:
		std::bitset<SHAPE_MATRIX_SIZE> GetShapeMatrix();
	private:
		std::bitset<SHAPE_MATRIX_SIZE> CreateShapeMatrix();
	};

	std::bitset<TILE_COUNT + 1 * SHAPE_MATRIX_SIZE>& GetShapesData();

	class EffectTile
	{
	public:
		enum EffectTileType : uint8_t
		{
			COUPON,
			STONE,
			ROBBERY
		};
	protected:
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
		public:
			Coordonates() {};
			Coordonates(uint8_t x, uint8_t y) : x(x), y(y) {};
		};
	protected:
		Coordonates coordonates;
	public:
		PlacedTile(PlacedTile::Coordonates coordonate);
		LayingGrass::PlacedTile::Coordonates GetCenterCoordonate();
		virtual void BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener);
		virtual PlayerId GetOwner();
	}; 

	LayingGrass::PlacedTile::Coordonates GetInvalidCoordonate();

	class PlacedEffectTile : public LayingGrass::PlacedTile, public LayingGrass::EffectTile {
	public:
		PlacedEffectTile(LayingGrass::PlacedTile::Coordonates coordonate, EffectTile::EffectTileType type);
	};

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
		PlacedShapedTile(LayingGrass::PlacedTile::Coordonates coordonate, Orientation orientation, PlayerId pid, uint8_t offset);
		virtual void BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener);
		virtual PlayerId GetOwner();
	};
}