#pragma once
#include "Toolbox.h"

int launch(); // Responsible for game launch
void render(); // Draws all UI elements according to gameState
void restart(); // Resets all states/objects and generates random board
void toggleDebugMode(); // Flips debug mode on/off
bool getDebugMode(); // getter for debugMode
void loadBoard1(); // Resets all states/objects and generates testboard1
void loadBoard2(); // Resets all states/objects and generates testboard2
void checkWin(); // checks win condition and updates gameState status


