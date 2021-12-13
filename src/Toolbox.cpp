#include "Toolbox.h"
#include "minesweeper.h"

Toolbox* Toolbox::instance = nullptr;
// Initializes instance to new Toolbox then returns it
Toolbox *Toolbox::getInstance() {
    if(instance == nullptr){
        instance = new Toolbox();
    }
    return instance;
}
// Memory deallocation called by destructor
void Toolbox::releaseInstance() {
    if(instance != nullptr)
        delete instance;
    if(gameState != nullptr)
        delete gameState;
    if(newGameButton != nullptr)
        delete newGameButton;
    if(debugButton != nullptr)
        delete debugButton;
    if(testButton1 != nullptr)
        delete testButton1;
    if(testButton2 != nullptr)
        delete testButton2;
}

Toolbox::Toolbox() {
    // Creates SFML Window and creates Random GameState
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Patrick Lapid");
    window.setFramerateLimit(60);
    gameState = new GameState();
    gameState->setPlayStatus(GameState::PLAYING);
    // Vectors for button creation
    sf::Vector2f newGamePos = sf::Vector2f (368, 512);
    sf::Vector2f debugButtonPos = sf::Vector2f (496, 512);
    sf::Vector2f testButton1Pos = sf::Vector2f (560, 512);
    sf::Vector2f testButton2Pos = sf::Vector2f (624, 512);
    // Creates each button
    newGameButton = new Button(newGamePos, restart);
    debugButton = new Button(debugButtonPos, toggleDebugMode);
    testButton1 = new Button(testButton1Pos, loadBoard1);
    testButton2 = new Button(testButton2Pos, loadBoard2);
}
