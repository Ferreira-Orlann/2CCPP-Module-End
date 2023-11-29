#include "layinggrass.hpp"
#include "visual.hpp"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style/style_cyber.h"

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
		std::shared_ptr<LayingGrass::VisualPlayer> ptr = std::shared_ptr<LayingGrass::VisualPlayer>(new VisualPlayer(picked));
		this->RegisterPlayer(ptr);
	}
}

void LayingGrass::LayingGrassVisual::DrawBoard()
{
	std::unique_ptr<LayingGrass::CollisionEngine> ptr = this->GetEngine();

	Rectangle rec;
	if (this->GetPlayerCount() < 5)
	{
		rec = { 100,100,(20*10)+(20*2),(20 * 10) + (20 * 2) + 4};
		DrawRectangleLinesEx(rec, 2, BLACK);


		for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

		}
		for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

		}
	}
	else
	{
		rec = { 0,0,0,0 };
		rec = { 100,100,(30 * 10) + (30 * 2),(30 * 10) + (30 * 2) + 4 };
		for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

		}
		for (auto it = ptr->EffectTilesBegin(); it != ptr->EffectTilesEnd(); ++it) {

		}
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
		case WAITING_SHAPED_TILE_PLACE:
			this->DrawBoard();
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