#ifndef GAME_H
#define GAME_H

#include <EEPROM.h>
#include "Menu.h"

// Game 1 constants
#define MIN_MOVE_INTERVAL 90
#define SPEEDUP_STEP 5
#define OBSTACLE_SPACE 4

// EEPROM addresses
#define EEPROM_HS1 0
#define EEPROM_HS2 4

// High scores
extern int highScore1;
extern int highScore2;

// Game 1
void Game1_init();
State Game1_update();

// Game 2
void Game2_init();
State Game2_update();

// High score management
void Game_loadHighScores();
void ResetHighScores();

#endif
