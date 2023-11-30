#include "tiles.hpp"
#include <cmath>

using namespace LayingGrass;

LayingGrass::PlacedShapedTile::PlacedShapedTile(LayingGrass::PlacedTile::Coordonates coordonate, Orientation orientation, PlayerId pid, uint8_t offset)
	: LayingGrass::PlacedTile(coordonate), LayingGrass::ShapedTile(offset)
{
	this->orientation = orientation;
	this->pid = pid;
}

LayingGrass::PlacedTile::Coordonates invalidCoordonate = LayingGrass::PlacedTile::Coordonates(UINT8_MAX, UINT8_MAX);
LayingGrass::PlacedTile::Coordonates LayingGrass::GetInvalidCoordonate()
{
	return invalidCoordonate;
}

LayingGrass::ShapedTile::ShapedTile(uint8_t offset)
{
	this->offset = offset;
	this->shapeBits = this->CreateShapeMatrix();
}

std::bitset<TILE_COUNT + 1 * SHAPE_MATRIX_SIZE> shapesData = std::bitset<TILE_COUNT + 1 * SHAPE_MATRIX_SIZE>();
std::bitset<TILE_COUNT + 1 * SHAPE_MATRIX_SIZE>& LayingGrass::GetShapesData()
{
	return shapesData;
}

std::bitset<SHAPE_MATRIX_SIZE> LayingGrass::ShapedTile::CreateShapeMatrix()
{
	std::bitset<SHAPE_MATRIX_SIZE> bitset;
	int bitOffset = offset * SHAPE_MATRIX_SIZE;
	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
	{
		bitset[i] = shapesData[bitOffset + i];
	}

	return bitset;
}

std::bitset<SHAPE_MATRIX_SIZE> LayingGrass::ShapedTile::GetShapeMatrix()
{
	return this->shapeBits;
}

LayingGrass::PlacedTile::Coordonates LayingGrass::PlacedTile::GetCenterCoordonate()
{
	return this->coordonates;
}

void LayingGrass::PlacedTile::BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener)
{
	contener.push_back(this->coordonates);
}

void AnticlockwiseRotateIntermediateMatrix(bool matrix[][SHAPE_HEIGHT], uint8_t interations)
{
	for (int z = 0; z < interations; z++)
	{
		for (int i = 0; i < SHAPE_HEIGHT / 2; i++)
		{
			for (int j = 0; j < SHAPE_HEIGHT - i - 1; j++)
			{
				bool temp = matrix[i][j];
				matrix[i][j] = matrix[j][SHAPE_HEIGHT - 1 - i];
				matrix[j][SHAPE_HEIGHT - 1 - i] = matrix[SHAPE_HEIGHT - 1 - i][SHAPE_HEIGHT - 1 - j];
				matrix[SHAPE_HEIGHT - 1 - i][SHAPE_HEIGHT - 1 - j] = matrix[SHAPE_HEIGHT - 1 - j][i];
				matrix[SHAPE_HEIGHT - 1 - j][i] = temp;
			}
		}
	}
}

void LayingGrass::PlacedShapedTile::BuildCoordonatesVector(std::vector<LayingGrass::PlacedTile::Coordonates>& contener)
{
	auto matrix = this->GetShapeMatrix();
	LayingGrass::PlacedTile::Coordonates center = this->GetCenterCoordonate();
	LayingGrass::PlacedTile::Coordonates top_left(center.x - std::floorf(SHAPE_HEIGHT/2), center.y - std::floorf(SHAPE_HEIGHT / 2));
	uint8_t x = 0;
	uint8_t y = 0;
	bool intermediateMatrix[SHAPE_HEIGHT][SHAPE_HEIGHT] = { 0 };
	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)	
	{
		bool bit = matrix[i];
		intermediateMatrix[x][y] = bit;
		x++;	
		if (x == SHAPE_HEIGHT)
		{
			x = 0;
			y++;
		}
	}
	switch (this->orientation)
	{
	case TOP:
		break;
	case DOWN:
		AnticlockwiseRotateIntermediateMatrix(intermediateMatrix, 2);
		break;
	case RIGHT:
		AnticlockwiseRotateIntermediateMatrix(intermediateMatrix, 3);
		break;
	case LEFT:
		AnticlockwiseRotateIntermediateMatrix(intermediateMatrix, 1);
		break;
	}
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_HEIGHT; j++)
		{
			bool bit = intermediateMatrix[i][j];
			if (!bit)
				continue;
			LayingGrass::PlacedTile::Coordonates coordonates(i + top_left.x, j + top_left.y);
			contener.push_back(coordonates);
		}
	}

}

PlayerId LayingGrass::PlacedTile::GetOwner()
{
	return PLAYER_NONE;
}

PlayerId LayingGrass::PlacedShapedTile::GetOwner()
{
	return this->pid;
}

LayingGrass::EffectTile::EffectTileType LayingGrass::EffectTile::GetType()
{
	return this->type;
}

LayingGrass::PlacedEffectTile::PlacedEffectTile(LayingGrass::PlacedTile::Coordonates coordonates, EffectTile::EffectTileType type) : EffectTile(), PlacedTile(coordonates)
{
	this->coordonates = coordonates;
	this->type = type;
}

LayingGrass::PlacedTile::PlacedTile(PlacedTile::Coordonates coordonates)
{
	this->coordonates = coordonates;
}