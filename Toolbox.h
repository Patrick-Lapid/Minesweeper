#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"

class Toolbox {
private:
    static Toolbox* instance; // The static singleton instance
    ~Toolbox(){ releaseInstance(); };
    Toolbox();
    void releaseInstance();

public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets/starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    static Toolbox* getInstance(); // Returns singleton instance
};


