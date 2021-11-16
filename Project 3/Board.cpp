#include "Board.h"
#include "TextureManager.h"
#include "Random.h"
#include <iostream>
using std::ifstream;
using std::getline;
using namespace std;

Board::Board() {
    // Load config.cfg data.
    ifstream file("boards/config.cfg");
    if (file.is_open()) {
        string temp;
        getline(file, temp);
        columns = stoi(temp);
        getline(file, temp);
        rows = stoi(temp);
        getline(file, temp);
        mineCount = stoi(temp);
    }
    tileCount = columns * rows;
    file.close();

    // Load tiles in a vector and set their position.
    int count = 0;
    while (count < tileCount) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < columns; k++) {
                Tile tile;
                tile.SetX(k * 32.0f);
                tile.SetY(j * 32.0f);
                tiles.push_back(tile);
                count++;
            }
        }
    }
    InitializeTiles();
    InitializeImages();
}

void Board::InitializeTiles() {
    Sprite mine(TextureManager::GetTexture("mine"));
    Sprite tile(TextureManager::GetTexture("tile_hidden"));
    Sprite flag(TextureManager::GetTexture("flag"));

    for (unsigned int i = 0; i < tiles.size(); i++) {
        tile.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
        tiles.at(i).SetTileSprite(tile);

        mine.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
        tiles.at(i).SetMineSprite(mine);

        flag.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
        tiles.at(i).SetFlagSprite(flag);
    }
}

void Board::InitializeImages() {
    face.setTexture(TextureManager::GetTexture("face_happy"));
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test3.setTexture(TextureManager::GetTexture("test_3"));
    debug.setTexture(TextureManager::GetTexture("debug"));
    face.setPosition(columns / 2.0f * 32.0f - 32.0f, rows * 32.0f);
    test1.setPosition(columns / 2.0f * 32.0f + 160.0f, rows * 32.0f);
    test2.setPosition(columns / 2.0f * 32.0f + 224.0f, rows * 32.0f);
    test3.setPosition(columns / 2.0f * 32.0f + 288.0f, rows * 32.0f);
    debug.setPosition(columns / 2.0f * 32.0f + 96.0f, rows * 32.0f);
}

int Board::GetColumns() {
    return columns;
}

int Board::GetRows() {
    return rows;
}

int Board::GetMineCount() {
    return mineCount;
}

int Board::GetTileCount() {
    return tileCount;
}

vector<Tile>& Board::GetTiles() {
    return tiles;
}

Sprite& Board::GetFaceSprite() {
    return face;
}

Sprite& Board::GetDebugSprite() {
    return debug;
}

Sprite& Board::GetTest1Sprite() {
    return test1;
}

Sprite& Board::GetTest2Sprite() {
    return test2;
}

Sprite& Board::GetTest3Sprite() {
    return test3;
}

void Board::SetAdjacentTiles() {
    Tile* bottom = nullptr;
    Tile* bottomRight = nullptr;
    Tile* bottomLeft = nullptr;
    Tile* top = nullptr;
    Tile* topRight = nullptr;
    Tile* topLeft = nullptr;
    Tile* right = nullptr;
    Tile* left = nullptr;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        vector<Tile*> adjacent;
        // Edge case: top left corner.
        if (i == 0) {
            right = &tiles.at(i + 1);
            bottom = &tiles.at(i + columns);
            bottomRight = &tiles.at(i + 1 + columns);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomRight);
            tiles.at(i).GetAdjacent().push_back(right);
        }
        // Edge case: bottom left corner.
        else if (i == tiles.size() - columns) {
            right = &tiles.at(i + 1);
            top = &tiles.at(i - columns);
            topRight = &tiles.at(i + 1 - columns);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topRight);
            tiles.at(i).GetAdjacent().push_back(right);
        }
        // Edge case: top right corner.
        else if (i == columns - 1) {
            left = &tiles.at(i - 1);
            bottom = &tiles.at(i + columns);
            bottomLeft = &tiles.at(i - 1 + columns);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomLeft);
            tiles.at(i).GetAdjacent().push_back(left);
        }
        // Edge case: bottom right corner.
        else if (i == tiles.size() - 1) {
            left = &tiles.at(i - 1);
            top = &tiles.at(i - columns);
            topLeft = &tiles.at(i - 1 - columns);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topLeft);
            tiles.at(i).GetAdjacent().push_back(left);
        }
        // Edge case: first column, excluding corners.
        else if (i % columns == 0 && i != 0 && i != tiles.size() - columns) {
            right = &tiles.at(i + 1);
            top = &tiles.at(i - columns);
            bottom = &tiles.at(i + columns);
            topRight = &tiles.at(i + 1 - columns);
            bottomRight = &tiles.at(i + 1 + columns);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomRight);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topRight);
            tiles.at(i).GetAdjacent().push_back(right);
        }
        // Edge case: last column, excluding corners.
        else if (i % columns == columns - 1 && i != columns - 1 && i != tiles.size() - 1) {
            left = &tiles.at(i - 1);
            top = &tiles.at(i - columns);
            bottom = &tiles.at(i + columns);
            topLeft = &tiles.at(i - 1 - columns);
            bottomLeft = &tiles.at(i - 1 + columns);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomLeft);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topLeft);
            tiles.at(i).GetAdjacent().push_back(left);
        }
        // Edge case: top row, excluding corners.
        else if (i > 0 && i < columns - 1) {
            bottom = &tiles.at(i + columns);
            left = &tiles.at(i - 1);
            right = &tiles.at(i + 1);
            bottomLeft = &tiles.at(i - 1 + columns);
            bottomRight = &tiles.at(i + 1 + columns);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomRight);
            tiles.at(i).GetAdjacent().push_back(bottomLeft);
            tiles.at(i).GetAdjacent().push_back(right);
            tiles.at(i).GetAdjacent().push_back(left);
        }
        // Edge case: bottom row, excluding corners.
        else if (i > tiles.size() - columns && i < tiles.size() - 1) {
            top = &tiles.at(i - columns);
            left = &tiles.at(i - 1);
            right = &tiles.at(i + 1);
            topLeft = &tiles.at(i - 1 - columns);
            topRight = &tiles.at(i + 1 - columns);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topRight);
            tiles.at(i).GetAdjacent().push_back(topLeft);
            tiles.at(i).GetAdjacent().push_back(right);
            tiles.at(i).GetAdjacent().push_back(left);
        }
        // All other cases.
        else {
            bottom = &tiles.at(i + columns);
            bottomRight = &tiles.at(i + 1 + columns);
            bottomLeft = &tiles.at(i - 1 + columns);
            top = &tiles.at(i - columns);
            topRight = &tiles.at(i + 1 - columns);
            topLeft = &tiles.at(i - 1 - columns);
            right = &tiles.at(i + 1);
            left = &tiles.at(i - 1);
            tiles.at(i).GetAdjacent().push_back(bottom);
            tiles.at(i).GetAdjacent().push_back(bottomRight);
            tiles.at(i).GetAdjacent().push_back(bottomLeft);
            tiles.at(i).GetAdjacent().push_back(top);
            tiles.at(i).GetAdjacent().push_back(topRight);
            tiles.at(i).GetAdjacent().push_back(topLeft);
            tiles.at(i).GetAdjacent().push_back(right);
            tiles.at(i).GetAdjacent().push_back(left);
        }
    }
    NumberHelper();
}

void Board::SetMineCount(int count) {
    mineCount = count;
}

void Board::NumberHelper() {
    Sprite number;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (!tiles.at(i).GetMine()) {
            int count = tiles.at(i).AdjacentMineCount();
            if (count == 1) {
                number.setTexture(TextureManager::GetTexture("number_1"));
            }
            else if (count == 2) {
                number.setTexture(TextureManager::GetTexture("number_2"));
            }
            else if (count == 3) {
                number.setTexture(TextureManager::GetTexture("number_3"));
            }
            else if (count == 4) {
                number.setTexture(TextureManager::GetTexture("number_4"));
            }
            else if (count == 5) {
                number.setTexture(TextureManager::GetTexture("number_5"));
            }
            else if (count == 6) {
                number.setTexture(TextureManager::GetTexture("number_6"));
            }
            else if (count == 7) {
                number.setTexture(TextureManager::GetTexture("number_7"));
            }
            else if (count == 8) {
                number.setTexture(TextureManager::GetTexture("number_8"));
            }
            number.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
            tiles.at(i).SetNumberSprite(number);
        }
    }
}

void Board::DrawTiles(RenderWindow& window) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        window.draw(tiles.at(i).GetTileSprite());
        if (!tiles.at(i).GetMine() && tiles.at(i).GetReveal() && tiles.at(i).AdjacentMineCount() != 0) {
            window.draw(tiles.at(i).GetNumberSprite());
        }
        if (tiles.at(i).GetFlag() && !tiles.at(i).GetReveal()) {
            window.draw(tiles.at(i).GetFlagSprite());
        }
        if (tiles.at(i).GetMine() && tiles.at(i).GetReveal()) {
            window.draw(tiles.at(i).GetMineSprite());
        }
        if (tiles.at(i).GetDebug() && tiles.at(i).GetMine()) {
            window.draw(tiles.at(i).GetMineSprite());
        }
    }
}

void Board::DrawImages(RenderWindow& window) {
    window.draw(face);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);
    window.draw(debug);

    // Count flags on board and update mine counter to reflect change.
    flagCount = 0;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tiles.at(i).GetFlag()) {
            flagCount++;
        }
    }
    DigitHelper(mineCount - flagCount);
    window.draw(digit1);
    window.draw(digit2);
    window.draw(digit3);

    // Account for if there are more flags than mines.
    if (mineCount - flagCount < 0) {
        window.draw(negative);
    }
}

void Board::DigitHelper(int value) {
    digit1.setTexture(TextureManager::GetTexture("digits"));
    digit2.setTexture(TextureManager::GetTexture("digits"));
    digit3.setTexture(TextureManager::GetTexture("digits"));
    negative.setTexture(TextureManager::GetTexture("digits"));

    if (value < 0) {
        value = abs(value);
    }

    // Hundredths place.
    int i = value / 100;
    int remainder = value % 100;
    digit1.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));

    // Tenths place.
    i = remainder / 10;
    remainder = value % 10;
    digit2.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));

    // Ones place.
    i = remainder / 1;
    remainder = value % 1;
    digit3.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));

    negative.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));

    digit1.setPosition(21.0f, rows * 32.0f);
    digit2.setPosition(42.0f, rows * 32.0f);
    digit3.setPosition(63.0f, rows * 32.0f);
    negative.setPosition(0.0f, rows * 32.0f);
}

void Board::Clear() {
    InitializeTiles();
    InitializeImages();
    for (unsigned int i = 0; i < tiles.size(); i++) {
        tiles.at(i).SetFlag(false);
        tiles.at(i).SetMine(false);
        tiles.at(i).SetReveal(false);
        tiles.at(i).GetAdjacent().clear();
        flagCount = 0;
    }
}

bool Board::CheckWin() {
    int revealedCount = 0;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (!tiles.at(i).GetMine() && tiles.at(i).GetReveal()) {
            revealedCount++;
        }
    }

    if (tileCount - mineCount == revealedCount ) {
        face.setTexture(TextureManager::GetTexture("face_win"));
        for (unsigned int i = 0; i < tiles.size(); i++) {
            if (tiles.at(i).GetMine()) {
                tiles.at(i).SetFlag(true);
                tiles.at(i).SetDebug(false);
            }
        }
        return true;
    }
    return false;
}

bool Board::CheckLose() {
    int minesRevealed = 0;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tiles.at(i).GetMine() && tiles.at(i).GetReveal()) {
            minesRevealed++;
        }
    }

    if (minesRevealed > 0) {
        face.setTexture(TextureManager::GetTexture("face_lose"));
        for (unsigned int i = 0; i < tiles.size(); i++) {
            if (tiles.at(i).GetMine()) {
                tiles.at(i).SetReveal(true);
            }
        }
        return true;
    }
    return false;
}

void Board::LoadBoard(string fileName) {
    ifstream file(fileName);
    string temp;
    vector<int> tempVector;
    if (file.is_open()) {
        while (getline(file, temp)) {
            for (unsigned int i = 0; i < temp.size(); i++) {
                if (temp.at(i) == '0') {
                    tempVector.push_back(0);
                }
                else if (temp.at(i) == '1') {
                    tempVector.push_back(1);
                }
            }
        }
    }
    file.close();
    mineCount = 0;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tempVector.at(i) == 1) {
            tiles.at(i).SetMine(true);
            mineCount++;
        }
    }
}