#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameState {
public:
    ~GameState();
    enum PlayStatus{ WIN, LOSS, PLAYING }; // tracks play status of game
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50); // random gameState constructor
    GameState(const char* filepath); // file input gameState constructor
    int getFlagCount(); // getter for flagCount
    int getMineCount(); // getter for mineCount
    Tile* getTile(int x, int y); // returns a pointer to Tile at specified coordinates
    PlayStatus getPlayStatus(); // getter for play status
    void setPlayStatus(PlayStatus _status); // setter for play status
private:
    int height = 0, width = 0, mineCount = 0;
    std::vector<Tile*> tileGrid; // Tile pointer grid
    void releaseArray(); // destructor for Tile array
    PlayStatus currStatus = PLAYING;
};

