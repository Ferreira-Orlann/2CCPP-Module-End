#pragma once

#include "layinggrass.hpp"
#include "raylib.h"

namespace LayingGrass
{
	class LayingGrassVisual : public LayingGrassInstance<VisualPlayer>
	{
	private:
		void WaitingForPlayers();
		void DrawBoard();
		void DrawNextTile();
		LayingGrass::PlacedTile::Coordonates BoardProcessInputs();
	public:
		LayingGrassVisual();
		void Render();
		void ProcessInputs();
		bool ShouldRender();
	};
}