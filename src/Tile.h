#pragma once
#include<array>
#include<SFML/Graphics.hpp>

class Tile {
public:
    enum State{REVEALED, HIDDEN, FLAGGED, EXPLODED}; // Represents tile's current UI state
    Tile(sf::Vector2f position); // Constructs new tile object
    void setState(State _state); // State setter
    State getState(); // State getter
    void setMine(); // Setter for isMine
    bool getMineStatus(); // Getter for isMine
    void setNeighbors(std::array<Tile*, 8> _neighbors); // Setter for Neighboring mines
    std::array<Tile*, 8>& getNeighbors(); // Getter for Neighbor array
    sf::Vector2f getLocation(); // Getter for vector coordinates
    void onClickLeft(); // left click function
    void onClickRight(); // right click function
    int getSurroundingMines() {return surroundingMines; }; // getter for surrounding mines
    void setSurroundingMines(int mineCount){ surroundingMines = mineCount; }; // setter for surrounding mines
    void draw(); // Renders tile to screen
private:
    bool isMine = false; // tracks if tile is mine
    State currState = HIDDEN;
    sf::Vector2f coords;
    sf::Vector2f drawingCoords; // specialized coordinate vector for rendering
    int surroundingMines = 0; // number that's rendered on tile
    std::array<Tile*, 8> Neighbors; // Neighbor array
    void drawNumber(); // renders number on tile
protected:
    void revealNeighbors(); // recursive function that reveals neighboring tiles if no bombs surround them
};

