#include "Tile.h"

Tile::Tile() {
	hasFlag = false;
	hasMine = false;
	hasDebug = false;
	isRevealed = false;
}

void Tile::SetX(float x) {
	this->x = x;
}

void Tile::SetY(float y) {
	this->y = y;
}

void Tile::SetReveal(bool status) {
	isRevealed = status;
}

void Tile::SetFlag(bool status) {
	hasFlag = status;
}

void Tile::SetMine(bool status) {
	hasMine = status;
}

void Tile::SetDebug(bool status) {
	hasDebug = status;
}

void Tile::SetTileSprite(Sprite sprite) {
	tile = sprite;
}

void Tile::SetFlagSprite(Sprite sprite) {
	flag = sprite;
}

void Tile::SetMineSprite(Sprite sprite) {
	mine = sprite;
}

void Tile::SetNumberSprite(Sprite sprite) {
	number = sprite;
}

float Tile::GetX() {
	return x;
}

float Tile::GetY() {
	return y;
}

bool Tile::GetFlag() {
	return hasFlag;
}

bool Tile::GetMine() {
	return hasMine;
}

bool Tile::GetDebug() {
	return hasDebug;
}

bool Tile::GetReveal() {
	return isRevealed;
}

vector<Tile*>& Tile::GetAdjacent() {
	return adjacent;
}

Sprite& Tile::GetTileSprite() {
	return tile;
}

Sprite& Tile::GetFlagSprite() {
	return flag;
}

Sprite& Tile::GetMineSprite() {
	return mine;
}

Sprite& Tile::GetNumberSprite() {
	return number;
}

int Tile::AdjacentMineCount() {
	int count = 0;
	for (unsigned int i = 0; i < adjacent.size(); i++) {
		if (adjacent.at(i) != nullptr && adjacent.at(i)->GetMine()) {
			count++;
		}
	}
	return count;
}

void Tile::RevealTiles() {
	Sprite revealed(TextureManager::GetTexture("tile_revealed"));
	for (unsigned int i = 0; i < adjacent.size(); i++) {
		if (adjacent.at(i) != nullptr && AdjacentMineCount() == 0 && !adjacent.at(i)->GetFlag() && !adjacent.at(i)->GetReveal()) {
			adjacent.at(i)->SetReveal(true);
			revealed.setPosition(adjacent.at(i)->GetX(), adjacent.at(i)->GetY());
			adjacent.at(i)->SetTileSprite(revealed);
			adjacent.at(i)->RevealTiles();
		}
	}
}