#pragma once

#include "layinggrass.hpp"
#include "raylib.h"

namespace LayingGrass
{
	class LayingGrassVisual : public LayingGrassInstance<VisualPlayer>
	{
	private:
		LayingGrass::PlacedShapedTile::Orientation orientation = LayingGrass::PlacedShapedTile::Orientation::TOP;
		void WaitingForPlayers();
		void DrawBoard();
		LayingGrass::PlacedTile::Coordonates BoardProcessInputs();
	public:
		LayingGrassVisual();
		void Render();
		void ProcessInputs();
		bool ShouldRender();
	};
}