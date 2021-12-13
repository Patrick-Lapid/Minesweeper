#include "minesweeper.h"
#include <iostream>
using namespace std;
// Toolbox instance and global variables
Toolbox* toolbox = Toolbox::getInstance();
int width, height;
bool debugState = false;

int launch() {
    // Opens main SFML window
    while(toolbox->window.isOpen()){
        sf::Event event;
        // Catches events from user
        while(toolbox->window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                toolbox->window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(toolbox->window);
                    // gets modified x and y coords for tile vector
                    int tileX = (mousePos.x / 32) + 1; int tileY = (mousePos.y / 32) + 1;
                    // If user clicks a non-flagged tile inside tile window
                    if(toolbox->gameState->getTile(tileX,tileY) != nullptr && toolbox->gameState->getPlayStatus() == GameState::PLAYING){

                        // Tile event handling on left click
                        if(toolbox->gameState->getTile(tileX,tileY)->getState() != Tile::FLAGGED){
                            toolbox->gameState->getTile(tileX, tileY)->onClickLeft();
                        }
                        // Checks Win Condition
                        checkWin();
                    }

                    // User clicks on restart button
                    else if((mousePos.x >= 368 && mousePos.x < 432) && (mousePos.y >= 512 && mousePos.y <= 576)){
                        toolbox->newGameButton->onClick();
                    }
                    // User clicks on debug button
                    else if((mousePos.x >= 496 && mousePos.x < 560) && (mousePos.y >= 512 && mousePos.y <= 576)){
                        toolbox->debugButton->onClick();
                    }
                    // User clicks on testBoard1 button
                    else if((mousePos.x >= 560 && mousePos.x < 624) && (mousePos.y >= 512 && mousePos.y <= 576)){
                        toolbox->testButton1->onClick();
                    }
                    // User clicks on testBoard2 button
                    else if((mousePos.x >= 624 && mousePos.x < 688) && (mousePos.y >= 512 && mousePos.y <= 576)){
                        toolbox->testButton2->onClick();
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(toolbox->window);
                    // gets modified x and y coords for tile vector
                    int tileX = (mousePos.x / 32) + 1; int tileY = (mousePos.y / 32) + 1;
                    // If user clicks inside tile window
                    if(toolbox->gameState->getTile(tileX,tileY) != nullptr && toolbox->gameState->getPlayStatus() == GameState::PLAYING){
                        toolbox->gameState->getTile(tileX, tileY)->onClickRight();
                        // Checks Win Condition
                        checkWin();
                    }
                }
            }
        }
        // Clears window with white, calls render function, and displays to window
        toolbox->window.clear(sf::Color::White);
        render();
        toolbox->window.display();
    }
    return 0;
}

void render(){
    width = 0; height = 0;
    // Generates width and height based on gameState Tile array
    while(toolbox->gameState->getTile(width + 1, 1) != nullptr){
        width++;
    }
    while(toolbox->gameState->getTile(1, height + 1) != nullptr){
        height++;
    }
    // Generates Tile board with custom height and width
    for(int y = 1; y <= height; y++){
        for(int x = 1; x <= width; x++){
            toolbox->gameState->getTile(x,y)->draw();
        }
    }
    // Loads button Textures and Sprites
    sf::Texture texture;
    sf::Sprite face;
    // Loads resetButton face based on gameState
    switch (toolbox->gameState->getPlayStatus()) {
        case (GameState::PLAYING):{
            texture.loadFromFile("images/face_happy.png");
            face.setTexture(texture);
            toolbox->newGameButton->setSprite(&face);
            break;
        }
        case (GameState::WIN):{
            texture.loadFromFile("images/face_win.png");
            face.setTexture(texture);
            toolbox->newGameButton->setSprite(&face);
            break;
        }
        case (GameState::LOSS):{
            texture.loadFromFile("images/face_lose.png");
            face.setTexture(texture);
            toolbox->newGameButton->setSprite(&face);
            break;
        }
    }
    // Draws reset button on screen
    toolbox->newGameButton->getSprite()->setPosition(sf::Vector2f(368,512));
    toolbox->window.draw(*toolbox->newGameButton->getSprite());
    // Draws debug button on screen
    texture.loadFromFile("images/debug.png");
    sf::Sprite debug(texture);
    toolbox->debugButton->setSprite(&debug);
    toolbox->debugButton->getSprite()->setPosition(sf::Vector2f(496, 512));
    toolbox->window.draw(*toolbox->debugButton->getSprite());
    // Draws testBoard1 button on screen
    texture.loadFromFile("images/test_1.png");
    sf::Sprite test1(texture);
    toolbox->testButton1->setSprite(&test1);
    toolbox->testButton1->getSprite()->setPosition(sf::Vector2f(560, 512));
    toolbox->window.draw(*toolbox->testButton1->getSprite());
    // Draws testBoard2 button on screen
    texture.loadFromFile("images/test_2.png");
    sf::Sprite test2(texture);
    toolbox->testButton2->setSprite(&test2);
    toolbox->testButton2->getSprite()->setPosition(sf::Vector2f(624, 512));
    toolbox->window.draw(*toolbox->testButton2->getSprite());

    //Adds MineCounter Textures + Sprites
    texture.loadFromFile("images/digits.png");
    sf::Sprite num1(texture);
    sf::Sprite num2(texture);
    sf::Sprite num3(texture);

    // Updates Flag counter Sprite based on current flags on board
    int flags = toolbox->gameState->getMineCount() - toolbox->gameState->getFlagCount();
    if(flags < -99)
        flags = -99;
    if(std::to_string(flags).size() == 1) {
        int digit1 = 0;
        num1.setTextureRect(sf::IntRect(digit1, 0, 21, 32));
        num2.setTextureRect(sf::IntRect(0, 0, 21, 32));
        int digit3 = flags;
        num3.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
    }

    else if (std::to_string(flags).size() == 2) {
        int digit1 = (flags >= 0 ? 0 : 10);
        num1.setTextureRect(sf::IntRect(digit1*21, 0, 21, 32));
        int digit2 = flags >= 0 ? (flags / 10) : 0;
        num2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
        int digit3 = flags >= 0 ? (flags % 10) : (-1 * flags);
        num3.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
    }

    else {
        int digit1 = (flags > 0 ? flags / 100: 10);
        num1.setTextureRect(sf::IntRect(digit1 * 21, 0, 21, 32));
        int digit2 = flags > 0 ? ((flags % 100) / 10) : (-1 * flags) / 10;
        num2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
        int digit3 = flags > 0 ? (flags % 10) : (-1 * flags) % 10;
        num3.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
    }
    // Draws flagCounter buttons
    num1.setPosition(sf::Vector2f(0, 512));
    toolbox->window.draw(num1);
    num2.setPosition(sf::Vector2f(21, 512));
    toolbox->window.draw(num2);
    num3.setPosition(sf::Vector2f(42, 512));
    toolbox->window.draw(num3);

    // Toggles mines based off of debugState value
    if(getDebugMode()){
        for(int y = 1; y <= height; y++){
            for(int x = 1; x <= width; x++){
                if(toolbox->gameState->getTile(x,y)->getMineStatus()){
                    // Draws hidden tile under mine
                    texture.loadFromFile("images/tile_hidden.png");
                    sf::Sprite hiddenTile(texture);
                    sf::Vector2f drawingCoords = toolbox->gameState->getTile(x,y)->getLocation();
                    drawingCoords.x *= 32; drawingCoords.y *= 32;
                    hiddenTile.setPosition(drawingCoords);
                    Toolbox::getInstance()->window.draw(hiddenTile);
                    // Draws mine on top of tile
                    texture.loadFromFile("images/mine.png");
                    sf::Sprite mine(texture);
                    mine.setPosition(drawingCoords);
                    Toolbox::getInstance()->window.draw(mine);
                }
            }
        }
    }
}
// Checks Game Ending state
void checkWin(){
    if(!(toolbox->gameState->getPlayStatus() == GameState::LOSS)){
        toolbox->gameState->setPlayStatus(GameState::WIN);
        for(int y = 1; y <= height; y++){
            for(int x = 1; x <= width; x++){
                if(!toolbox->gameState->getTile(x,y)->getMineStatus() && toolbox->gameState->getTile(x,y)->getState() == Tile::HIDDEN){
                    toolbox->gameState->setPlayStatus(GameState::PLAYING);
                    break;
                }
            }
        }
    }
}

// Deletes old gameState and renders new one
void restart(){
    debugState = false;
    delete toolbox->gameState;
    toolbox->gameState = new GameState;
    render();
}

// toggles debugState bool value
void toggleDebugMode(){
    if(getDebugMode())
        debugState = false;
    else
        debugState = true;
}

// returns debugState bool
bool getDebugMode(){
    return debugState;
}
// deletes old gameState and renders testBoard1
void loadBoard1(){
    debugState = false;
    delete toolbox->gameState;
    toolbox->gameState = new GameState("boards/testboard1.brd");
    toolbox->gameState->setPlayStatus(GameState::PLAYING);
    render();
}
// deletes old gameState and renders testBoard2
void loadBoard2(){
    debugState = false;
    delete toolbox->gameState;
    toolbox->gameState = new GameState("boards/testboard2.brd");
    toolbox->gameState->setPlayStatus(GameState::PLAYING);
    render();
}