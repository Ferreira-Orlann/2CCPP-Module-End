#pragma once

#include "layinggrass.hpp"
#include "raylib.h"

namespace LayingGrass
{
	class LayingGrassVisual : public LayingGrassInstance<VisualPlayer>
	{
	private:
		void WaitingForPlayers();
	public:
		LayingGrassVisual();
		void Render();
		void ProcessInputs();
		bool ShouldRender();
		void DrawBoard();
	};
}