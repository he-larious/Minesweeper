#pragma once
#include "Tile.h"
#include <fstream>
#include <SFML/Graphics.hpp>
using sf::Texture;
using sf::RenderWindow;

class Board {
private:
    int columns;
    int rows;
    int mineCount;
    int tileCount;
    int flagCount;
    vector<Tile> tiles;
    Sprite face;
    Sprite test1;
    Sprite test2;
    Sprite test3;
    Sprite debug;
    Sprite digit1;
    Sprite digit2;
    Sprite digit3;
    Sprite negative;

public:
    Board();
    void InitializeTiles();
    void InitializeImages();
    int GetColumns();
    int GetRows();
    int GetMineCount();
    int GetTileCount();
    vector<Tile>& GetTiles();
    Sprite& GetFaceSprite();
    Sprite& GetDebugSprite();
    Sprite& GetTest1Sprite();
    Sprite& GetTest2Sprite();
    Sprite& GetTest3Sprite();
    void SetAdjacentTiles();
    void SetMineCount(int count);
    void NumberHelper();
    void DrawTiles(RenderWindow& window);
    void DrawImages(RenderWindow& window);
    void DigitHelper(int value);
    void Clear();
    bool CheckWin();
    bool CheckLose();
    void LoadBoard(string fileName);
};
