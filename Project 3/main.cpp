#include "Board.h"
#include "Tile.h"
#include "Random.h"
#include "TextureManager.h"
#include <SFML/graphics.hpp>
#include <iostream>
using namespace std;
using sf::Event;
using sf::Mouse;

void DrawOnTile(RenderWindow& window, vector<Tile>& tiles, string click);
void ClickImage(RenderWindow& window, Board& board);
void RandomGenMines(Board& board);

int main() {
    Board board;  // Call default constructor that loads config.cfg data.
    int width = board.GetColumns() * 32;
    int height = board.GetRows() * 32 + 88;

	RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    RandomGenMines(board);
    board.SetAdjacentTiles();

    while (window.isOpen()) {
        Event event;
        window.clear(sf::Color::White);
        board.DrawTiles(window);
        board.DrawImages(window);

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                TextureManager::Clear();
                window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (!board.CheckWin() && !board.CheckLose()) {
                        DrawOnTile(window, board.GetTiles(), "left");
                    }
                    ClickImage(window, board);
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    if (!board.CheckWin() && !board.CheckLose()) {
                        DrawOnTile(window, board.GetTiles(), "right");
                    }
                }
            }
        }
        window.display();
    }

	return 0;
}

// I'm so sorry that this function is such a mess...
void DrawOnTile(RenderWindow& window, vector<Tile>& tiles, string click) {
    Sprite revealed(TextureManager::GetTexture("tile_revealed"));
    Sprite hidden(TextureManager::GetTexture("tile_hidden"));

    sf::Vector2i mousePos = Mouse::getPosition(window);

    for (unsigned int i = 0; i < tiles.size(); i++) {
        auto bounds = tiles.at(i).GetTileSprite().getGlobalBounds();
        if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
            // Draw revealed tile when you left click on a tile with no flag.
            if (click == "left" && !tiles.at(i).GetFlag()) {
                revealed.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
                tiles.at(i).SetTileSprite(revealed);
                tiles.at(i).SetReveal(true);
                window.draw(revealed);

                // Recursively reveal tiles if clicked on tile with no adjacent mines.
                if (!tiles.at(i).GetMine()) {
                    tiles.at(i).RevealTiles();
                }

                // Draw number if there are adjacent mines.
                if (tiles.at(i).AdjacentMineCount() != 0 && !tiles.at(i).GetMine()) {
                    window.draw(tiles.at(i).GetNumberSprite());
                }

                // Draw mine if you reveal a tile with a mine on it.
                if (tiles.at(i).GetMine()) {
                    window.draw(tiles.at(i).GetMineSprite());
                }
            }
            // Draw flag when you right click on a tile that is hidden and has no flag.
            if (click == "right" && !tiles.at(i).GetReveal() && !tiles.at(i).GetFlag()) {
                tiles.at(i).SetFlag(true);
                window.draw(tiles.at(i).GetFlagSprite());
            }
            // Remove flag when you right click on a hidden tile that already has a flag.
            else if (click == "right" && tiles.at(i).GetFlag()) {
                hidden.setPosition(tiles.at(i).GetX(), tiles.at(i).GetY());
                tiles.at(i).SetTileSprite(hidden);
                tiles.at(i).SetFlag(false);
                window.draw(hidden);
            }
        }
    }
}

void ClickImage(RenderWindow& window, Board& board) {
    sf::Vector2i mousePos = Mouse::getPosition(window);
    // If debug is clicked...
    auto bounds = board.GetDebugSprite().getGlobalBounds();
    if (!board.CheckWin() && !board.CheckLose()) {
        if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
            for (unsigned int i = 0; i < board.GetTiles().size(); i++) {
                if (!board.GetTiles().at(i).GetDebug()) {
                    board.GetTiles().at(i).SetDebug(true);
                }
                else {
                    board.GetTiles().at(i).SetDebug(false);
                }
            }
        }
    }
    // If smiley face is clicked...
    bounds = board.GetFaceSprite().getGlobalBounds();
    if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
        board.Clear();
        RandomGenMines(board);
        board.SetAdjacentTiles();
    }
    // Test 1.
    bounds = board.GetTest1Sprite().getGlobalBounds();
    if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
        board.Clear();
        board.LoadBoard("boards/testboard1.brd");
        board.SetAdjacentTiles();
    }
    // Test 2.
    bounds = board.GetTest2Sprite().getGlobalBounds();
    if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
        board.Clear();
        board.LoadBoard("boards/testboard2.brd");
        board.SetAdjacentTiles();
    }
    // Test 3.
    bounds = board.GetTest3Sprite().getGlobalBounds();
    if (bounds.contains((float)mousePos.x, (float)mousePos.y)) {
        board.Clear();
        board.LoadBoard("boards/testboard3.brd");
        board.SetAdjacentTiles();
    }
}

void RandomGenMines(Board& board) {
    /* Error with resetting board's original mine count after test boards were loaded,
     * fixed by reloading default constructor with mine count from config.cfg.
     */
    Board temp;
    board.SetMineCount(temp.GetMineCount());
    int count = 0;
    while (count < temp.GetMineCount()) {
        int temp = Random::RandomInt(0, board.GetTiles().size() - 1);
        for (unsigned int i = 0; i < board.GetTiles().size(); i++) {
            if (i == temp && !board.GetTiles().at(temp).GetMine()) {
                board.GetTiles().at(temp).SetMine(true);
                count++;
                break;
            }
        }
    }
}