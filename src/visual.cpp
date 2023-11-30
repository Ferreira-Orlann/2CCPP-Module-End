#include "layinggrass.hpp"
#include "visual.hpp"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style/style_cyber.h"

#include <cmath>
#include <format>

LayingGrass::LayingGrassVisual::LayingGrassVisual()
{
	InitWindow(1080, 720, "LayingGrass");
	SetTargetFPS(60);
	GuiLoadStyleCyber();
}

void LayingGrass::LayingGrassVisual::DrawNextTile()
{
	std::vector<LayingGrass::PlacedTile::Coordonates> vec = std::vector<LayingGrass::PlacedTile::Coordonates>();
	this->BuildNextShapedTile().BuildCoordonatesVector(vec);
	Color c = GREEN;
	for (LayingGrass::PlacedTile::Coordonates coordonate : vec)
	{

		Rectangle cell = { 700 + 20 * coordonate.x, 160 + 20 * coordonate.y, 20, 20 };
		DrawRectangleRec(cell, c);
	}
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_HEIGHT; j++)
		{
			Rectangle cell = { 700 + 20 * i, 160 + 20 * j, 20, 20 };
			DrawRectangleLinesEx(cell, 1, BLACK);
		}
	}
}

void LayingGrass::LayingGrassVisual::WaitingForPlayers()
{
	Rectangle rec = Rectangle(340, 160, 400, 400);
	GuiWindowBox(rec, "Ajouter un joueur");
	bool click =  GuiButton(Rectangle(340 + 20, 160 + 20, 380, 20), "Ajouter");
	static Color picked = WHITE;
	GuiColorPicker(Rectangle(340 + 20, 160 + 20 + 50, 360, 200), "Couleur du joueur", &picked);
	if (click)
	{
		std::shared_ptr<LayingGrass::VisualPlayer> ptr = std::shared_ptr<LayingGrass::VisualPlayer>(new VisualPlayer(picked, this->GetPlayerCount()));
		this->RegisterPlayer(ptr);
	}
	click = GuiButton(Rectangle(340 + 45, 160 + 45, 380, 20), std::format("{}{}{}", "Start: ", this->GetPlayerCount(), " Joueurs").c_str());
	if (click && this->GetPlayerCount() > 1)
	{
		this->Start();
	}
}

void LayingGrass::LayingGrassVisual::DrawBoard()
{
	LayingGrass::CollisionEngine engine = this->GetEngine();

	Rectangle rec;
	if (this->GetPlayerCount() < 5)
	{
		rec = { 100, 100, (20*20), (20 * 20) };
		DrawRectangleLinesEx(rec, 2, BLACK);

		for (PlacedEffectTile tile : engine.GetPlacedEffectTileVector()) {
			Rectangle cell = { rec.x + 20 * tile.GetCenterCoordonate().x, rec.y + 20 * tile.GetCenterCoordonate().y, 20, 20};
			DrawRectangleRec(cell, BLACK);
			switch (tile.GetType())
			{
			case LayingGrass::PlacedEffectTile::STONE:
				DrawText("S", cell.x, cell.y, 13, WHITE);
				break;
			case LayingGrass::PlacedEffectTile::ROBBERY:
				DrawText("R", cell.x, cell.y, 13, WHITE);
				break;
			case LayingGrass::PlacedEffectTile::COUPON:
				DrawText("C", cell.x, cell.y, 13, WHITE);
				break;
			}
		}

		for (PlacedShapedTile tile : engine.GetPlacedShapedTileVector()) {
			std::vector<LayingGrass::PlacedTile::Coordonates> vec = std::vector<LayingGrass::PlacedTile::Coordonates>();
			tile.BuildCoordonatesVector(vec);
			Color c = this->GetPlayer(tile.GetOwner())->GetColor();
			for (LayingGrass::PlacedTile::Coordonates coordonate : vec)
			{
				Rectangle cell = { rec.x + 20 * coordonate.x, rec.y + 20 * coordonate.y, 20, 20 };
				DrawRectangleRec(cell, c);
			}
		}

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				Rectangle cell = { rec.x + 20 * i, rec.y + 20 * j, 20, 20 };
				DrawRectangleLinesEx(cell, 1, BLACK);
			}
		}
	}
	else
	{
		rec = { 100, 100, (30 * 20), (30 * 20) };
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
		case TERRITORY:
			this->DrawBoard();
			break;
		case WAITING_SHAPED_TILE_PLACE:
			this->DrawBoard();
			this->DrawNextTile();
			break;
		}
		ClearBackground(DARKGRAY);
	EndDrawing();
}

LayingGrass::PlacedTile::Coordonates LayingGrass::LayingGrassVisual::BoardProcessInputs()
{
	Rectangle rec;
	uint8_t boardSize;
	if (this->GetPlayerCount() < 5)
	{
		boardSize = 20;
	}
	else
	{
		boardSize = 30;
	}
	rec = { 100, 100, (float) (boardSize * 20), (float) (boardSize * 20) };
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		return GetInvalidCoordonate();
	}
	Vector2 vec2 = GetMousePosition();
	if (!CheckCollisionPointRec(vec2, rec))
	{
		return GetInvalidCoordonate();
	}
	return LayingGrass::PlacedEffectTile::Coordonates((int) std::floorf((vec2.x - rec.x) / boardSize), (int) std::floorf((vec2.y - rec.y) / boardSize));
}

void LayingGrass::LayingGrassVisual::ProcessInputs()
{
	LayingGrass::PlacedTile::Coordonates boardCoordonates = this->BoardProcessInputs();
	LayingGrass::PlacedTile::Coordonates invalidCoordonates = GetInvalidCoordonate();
	if (IsKeyPressed(KEY_R))
	{
		switch (this->orientation)
		{
		case LayingGrass::PlacedShapedTile::Orientation::TOP:
			this->orientation = LayingGrass::PlacedShapedTile::Orientation::RIGHT;
			break;
		case LayingGrass::PlacedShapedTile::Orientation::DOWN:
			this->orientation = LayingGrass::PlacedShapedTile::Orientation::LEFT;
			break;
		case LayingGrass::PlacedShapedTile::Orientation::RIGHT:
			this->orientation = LayingGrass::PlacedShapedTile::Orientation::DOWN;
			break;
		case LayingGrass::PlacedShapedTile::Orientation::LEFT:
			this->orientation = LayingGrass::PlacedShapedTile::Orientation::TOP;
			break;
		}
		
	}
	switch (this->GetGameState())
	{
	case WAITING_FOR_PLAYERS:
		break;
	case TERRITORY:
		if (boardCoordonates.x == invalidCoordonates.x or boardCoordonates.y == invalidCoordonates.y)
		{
			break;
		}
		this->PlaceTileEx(boardCoordonates, this->orientation, SHAPE_COUNT);
		break;
	case WAITING_SHAPED_TILE_PLACE:
		if (boardCoordonates.x == invalidCoordonates.x or boardCoordonates.y == invalidCoordonates.y)
		{
			break;
		}
		this->PlaceTile(boardCoordonates, this->orientation);
		break;
	}
}

bool LayingGrass::LayingGrassVisual::ShouldRender()
{
	return !(!WindowShouldClose() && IsKeyDown(KEY_ESCAPE));
}