#include "player.hpp"

void LayingGrass::Player::SetPlayerId(LayingGrass::PlayerId id)
{
	this->id = id;
}

LayingGrass::VisualPlayer::VisualPlayer(Color c, PlayerId id)
{
	this->color = c;
	this->SetPlayerId(id);
}

Color LayingGrass::VisualPlayer::GetColor()
{
	return this->color;
}