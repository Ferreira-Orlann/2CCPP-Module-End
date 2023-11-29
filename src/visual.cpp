#include "visual.hpp"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style/style_cyber.h"
#include <iostream>

LayingGrass::LayingGrassVisual::LayingGrassVisual()
{
	InitWindow(1080, 720, "LayingGrass");
	SetTargetFPS(60);
	GuiLoadStyleCyber();
}

void LayingGrass::LayingGrassVisual::WaitingForPlayers()
{
	Rectangle rec = Rectangle(340, 160, 400, 400);
	GuiWindowBox(rec, "Ajouter un joueur");
	rec = Rectangle(340 + 20, 160 + 20, 380, 20);
	bool click =  GuiButton(rec, "Ajouter");
	static Color picked = WHITE;
	GuiColorPicker(Rectangle(340 + 20, 160 + 20 + 50, 360, 200), "Couleur du joueur", &picked);
	if (click)
	{
		this->RegisterPlayer(std::make_shared<VisualPlayer>(new VisualPlayer(picked)));
	}
}

void LayingGrass::LayingGrassVisual::DrawBoard()
{
	std::unique_ptr<LayingGrass::CollisionEngine> ptr = this->GetEngine();

	for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

	}
	for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

	}
}

void LayingGrass::LayingGrassVisual::Render()
{
	BeginDrawing();
		switch (this->GetGameState())
		{
		case WAITING_FOR_PLAYERS:
			WaitingForPlayers();
			break;
		default:
			break;
		}
		ClearBackground(DARKGRAY);
	EndDrawing();
}

void LayingGrass::LayingGrassVisual::ProcessInputs()
{

}

bool LayingGrass::LayingGrassVisual::ShouldRender()
{
	return !(!WindowShouldClose() && IsKeyDown(KEY_ESCAPE));
}