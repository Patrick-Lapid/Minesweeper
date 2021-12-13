#include "Tile.h"
#include "Toolbox.h"
#include <array>
// Tile
Tile::Tile(sf::Vector2f position) {
    coords = position;
    drawingCoords = position;
    drawingCoords.x *=32; drawingCoords.y *=32;
    for(int x = 0; x < 8; x++){
        Neighbors[x] = nullptr;
    }
}

// Draws tile on screen depending on state
void Tile::draw() {
    sf::Texture texture;
    if(currState == HIDDEN){
        texture.loadFromFile("images/tile_hidden.png");
        sf::Sprite hiddenTile(texture);
        hiddenTile.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(hiddenTile);
    }
    else if(currState == REVEALED){
        texture.loadFromFile("images/tile_revealed.png");
        sf::Sprite revealedTile(texture);
        revealedTile.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(revealedTile);
        drawNumber();
    }
    else if(currState == FLAGGED){
        // Draws hidden tile under flag
        texture.loadFromFile("images/tile_hidden.png");
        sf::Sprite hiddenTile(texture);
        hiddenTile.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(hiddenTile);

        texture.loadFromFile("images/flag.png");
        sf::Sprite flag(texture);
        flag.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(flag);
    }
    else if(currState == EXPLODED){
        // Draws hidden tile under mine
        texture.loadFromFile("images/tile_hidden.png");
        sf::Sprite hiddenTile(texture);
        hiddenTile.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(hiddenTile);

        texture.loadFromFile("images/mine.png");
        sf::Sprite mine(texture);
        mine.setPosition(drawingCoords);
        Toolbox::getInstance()->window.draw(mine);
    }
}

// Sets tile to mine
void Tile::setMine() {
    isMine = true;
}
// Returns true if mine, false otherwise
bool Tile::getMineStatus() {
    return isMine;
}

// Sets state of tile when called
void Tile::setState(Tile::State _state) {
    currState = _state;
}
// Returns state of tile when called
Tile::State Tile::getState() {
    return currState;
}
// Returns vector of neighboring tile pointers
std::array<Tile *, 8> &Tile::getNeighbors() {
    return Neighbors;
}
// Sets vector of neighboring tile pointers
void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    for(int x = 0; x < 8; x++){
        Neighbors[x] = _neighbors[x];
    }
}
// Returns tile coordinates
sf::Vector2f Tile::getLocation() {
    return coords;
}
// Defines left click behavior
void Tile::onClickLeft() {
    if(isMine){
        currState = EXPLODED;
        draw();
        Toolbox::getInstance()->gameState->setPlayStatus(GameState::LOSS);
    } else {
        currState = REVEALED;
        if(surroundingMines == 0)
            revealNeighbors();
        draw();
    }
}
// Defines right click behavior
void Tile::onClickRight() {
    if(currState == REVEALED || currState == EXPLODED)
        return;
    if(currState != FLAGGED){
        currState = FLAGGED;
        draw();
    } else {
        currState = HIDDEN;
        draw();
    }
}

// Draws number over revealed tile based off of surrounding mines
void Tile::drawNumber() {
    sf::Texture texture;
    switch (surroundingMines) {
        case 1:{
            texture.loadFromFile("images/number_1.png");
            sf::Sprite num1(texture);
            num1.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num1);
            break;
        }
        case 2:{
            texture.loadFromFile("images/number_2.png");
            sf::Sprite num2(texture);
            num2.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num2);
            break;
        }
        case 3:{
            texture.loadFromFile("images/number_3.png");
            sf::Sprite num3(texture);
            num3.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num3);
            break;
        }
        case 4:{
            texture.loadFromFile("images/number_4.png");
            sf::Sprite num4(texture);
            num4.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num4);
            break;
        }
        case 5:{
            texture.loadFromFile("images/number_5.png");
            sf::Sprite num5(texture);
            num5.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num5);
            break;
        }
        case 6:{
            texture.loadFromFile("images/number_6.png");
            sf::Sprite num6(texture);
            num6.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num6);
            break;
        }
        case 7:{
            texture.loadFromFile("images/number_7.png");
            sf::Sprite num7(texture);
            num7.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num7);
            break;
        }
        case 8:{
            texture.loadFromFile("images/number_8.png");
            sf::Sprite num8(texture);
            num8.setPosition(drawingCoords);
            Toolbox::getInstance()->window.draw(num8);
            break;
        }
        default:
            break;
    }
}
// Generates Recursive algorithm that reveals neighboring tiles if they have no surrounding bombs
void Tile::revealNeighbors() {
    for(int i = 1; i < 8; i++){
        if(Neighbors[i] != nullptr && (!Neighbors[i]->getMineStatus())){
            // Runs revealNeighbors if surrounding tile is a blank tile
            if(Neighbors[i]->getSurroundingMines() == 0 && Neighbors[i]->getState() == HIDDEN){
                Neighbors[i]->setState(REVEALED);
                Neighbors[i]->draw();
                Neighbors[i]->revealNeighbors();
            }
            // Reveals numbers bordering bombs
            else if(Neighbors[i]->getSurroundingMines() != 0 && Neighbors[i]->getState() == HIDDEN){
                Neighbors[i]->setState(REVEALED);
                Neighbors[i]->draw();
            }
        }
    }
}




