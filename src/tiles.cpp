#include "tiles.hpp"

using namespace LayingGrass;

LayingGrass::ShapedTile::ShapedTile(uint8_t offset)
{
	this->offset = offset;
	this->shapeBits = this->CreateShapeMatrix();
}

std::bitset<SHAPE_MATRIX_SIZE> LayingGrass::ShapedTile::CreateShapeMatrix()
{
	std::bitset<SHAPE_MATRIX_SIZE> bitset;
	int bitOffset = offset * SHAPE_MATRIX_SIZE;
	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
	{
		bitset[i] = LayingGrass::shapesData[bitOffset + i];
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
	LayingGrass::PlacedTile::Coordonates top_left(center.x - 2, center.y - 2);
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

	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
	{
		bool bit = matrix[i];
		if (!bit)
			continue;
		LayingGrass::PlacedTile::Coordonates coordonates(x + top_left.x, y + top_left.y);
		contener.push_back(coordonates);
		x++;
		if (x == SHAPE_HEIGHT)
		{
			x = 0;
			y++;
		}
	}
	x = 0;
	y = 0;
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