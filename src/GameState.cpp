#include "GameState.h"
#include "Toolbox.h"
#include <fstream>

// Destructor for gamestate
GameState::~GameState() {
    if(tileGrid.at(0) != nullptr)
        releaseArray();
}
// Memory deallocation for Tile array
void GameState::releaseArray() {
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            delete tileGrid.at(width * (y - 1) + (x - 1));
        }
    }
}
// Gamestate constructor for dimension parameters
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    width = _dimensions.x;
    height = _dimensions.y;
    mineCount = _numberOfMines;
    int availMines = mineCount;
    // Generates Vector of Tiles
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            tileGrid.push_back(new Tile(sf::Vector2f(x, y)));
        }
    }
    // Generating random minefield
    srand(time(NULL));
    while(availMines > 0){
        int index = std::rand()%(width*height - 1);
        if(!tileGrid.at(index)->getMineStatus()){
            tileGrid.at(index)->setMine();
            availMines--;
        }
    }
    // Generates neighboring tile array for each tile
    std::array<Tile*, 8> Neighbors;
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            int mineCount = 0;
            Neighbors = getTile(x,y)->getNeighbors();
            Neighbors[0] = getTile(x - 1, y - 1);
            Neighbors[1] = getTile(x, y - 1);
            Neighbors[2] = getTile(x + 1, y - 1);
            Neighbors[3] = getTile(x - 1, y);
            Neighbors[4] = getTile(x + 1, y);
            Neighbors[5] = getTile(x - 1, y + 1);
            Neighbors[6] = getTile(x, y + 1);
            Neighbors[7] = getTile(x + 1, y + 1);
            for(int arrayIter = 0; arrayIter < 8; arrayIter++){
                if(Neighbors[arrayIter] != nullptr && Neighbors[arrayIter]->getMineStatus())
                    mineCount++;
            }
            getTile(x,y)->setNeighbors(Neighbors);
            getTile(x,y)->setSurroundingMines(mineCount);
        }
    }
}
// GameState constructor for user files
GameState::GameState(const char* filepath) {
    width = -1;
    std::ifstream myFile(filepath);
    std::vector<char> charVec;
    bool firstRow = true;
    char temp;
    if(myFile.is_open()){
        while(myFile >> std::noskipws >> temp){
            // Checks for newline to find width of board
            if(firstRow)
                width++;
            if(temp == '\n'){
                firstRow = false;
                continue;
            }
            // Checks for '1' to find mineCount
            if(temp == '1')
                mineCount++;
            charVec.push_back(temp);
        }
    }
    myFile.close();
    // calculates width using vector size and height
    height = charVec.size() / width;
    // Populates tile grid with given dimensions
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            tileGrid.push_back(new Tile(sf::Vector2f(x, y)));
        }
    }
    // Generates mines based on given board file
    for(int x = 0; x < charVec.size(); x++){
        if(charVec.at(x) == '1'){
            tileGrid.at(x)->setMine();
        }
    }

    // Generates neighboring tile array for each tile
    std::array<Tile*, 8> Neighbors;
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            int mineCount = 0;
            Neighbors = getTile(x,y)->getNeighbors();
            Neighbors[0] = getTile(x - 1, y - 1);
            Neighbors[1] = getTile(x, y - 1);
            Neighbors[2] = getTile(x + 1, y - 1);
            Neighbors[3] = getTile(x - 1, y);
            Neighbors[4] = getTile(x + 1, y);
            Neighbors[5] = getTile(x - 1, y + 1);
            Neighbors[6] = getTile(x, y + 1);
            Neighbors[7] = getTile(x + 1, y + 1);
            for(int arrayIter = 0; arrayIter < 8; arrayIter++){
                if(Neighbors[arrayIter] != nullptr && Neighbors[arrayIter]->getMineStatus())
                    mineCount++;
            }
            getTile(x,y)->setNeighbors(Neighbors);
            getTile(x,y)->setSurroundingMines(mineCount);
        }
    }
}

// Returns pointer to tile given x and y coords
Tile *GameState::getTile(int x, int y) {
    // Returns specific tile with given coords
    if((x > this->width || x < 1) || (y > this->height || y < 1)){
        return nullptr;
    } else {
        int index = width * (y - 1) + (x - 1);
        return tileGrid.at(index);
    }
}
// Returns number of flags on board
int GameState::getFlagCount() {
    int flagCount = 0;
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            if(tileGrid.at(width * (y - 1) + (x - 1))->getState() == Tile::FLAGGED)
                flagCount++;
        }
    }
    return flagCount;
}
// Returns current number of mines on board
int GameState::getMineCount() {
    int mineCount = 0;
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            if(tileGrid.at(width * (y - 1) + (x - 1))->getMineStatus())
                mineCount++;
        }
    }
    return mineCount;
}
// getter for GameState PlayStatus
GameState::PlayStatus GameState::getPlayStatus() {
    return currStatus;
}
// setter for Gamestate PlayStatus
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    currStatus = _status;
}


