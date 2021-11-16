#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using std::vector;
using sf::Sprite;
using sf::RenderWindow;

class Tile {
private:
	float x;
	float y;
	bool hasFlag;
	bool hasMine;
	bool hasDebug;
	bool isRevealed;
	vector<Tile*> adjacent;
	Sprite tile;
	Sprite flag;
	Sprite mine;
	Sprite number;

public:
	Tile();
	void SetX(float x);
	void SetY(float y);
	void SetReveal(bool status);
	void SetFlag(bool status);
	void SetMine(bool status);
	void SetDebug(bool status);
	void SetTileSprite(Sprite sprite);
	void SetFlagSprite(Sprite sprite);
	void SetMineSprite(Sprite sprite);
	void SetNumberSprite(Sprite sprite);
	float GetX();
	float GetY();
	bool GetFlag();
	bool GetMine();
	bool GetDebug();
	bool GetReveal();
	vector<Tile*>& GetAdjacent();
	Sprite& GetTileSprite();
	Sprite& GetFlagSprite();
	Sprite& GetMineSprite();
	Sprite& GetNumberSprite();
	int AdjacentMineCount();
	void RevealTiles();
};
