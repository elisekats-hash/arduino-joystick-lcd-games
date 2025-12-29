#include "Game.h"
#include "Display.h"
#include "Input.h"

// ------------- Global variables -------------
// Game 1
int player1_x = 2; 
int player1_y = 1;
bool gameover1 = false; 
int score1 = 0;
bool jumping = false; 
unsigned long jumpStartTime = millis();
unsigned long lastMoveTime = millis(); 
unsigned long moveInterval = 350;
const unsigned long jumpDuration = 400;
int wall1_x = 15; 
int wall1_y = 1;
int wall3_x = 15 + random(6, 10);
int wall3_y = 1;
int tree_x = wall1_x + OBSTACLE_SPACE; 
int tree_y = 1;

// Game 2
int player2_x = 8;
int player2_y = 1;
int gameover2 = false; 
int score2 = 0;
int wall2_x = 13; 
int wall2_y = 0;
int projectile_x = 4; 
int projectile_y = 0;
unsigned long lastFallTime = millis(); 
unsigned long fallInterval = 600;

//High Scores
int highScore1 = 0;
int highScore2 = 0;

// ------------- Initialization -------------
void Game1_init(){
  player1_x = 2; player1_y = 1;
  gameover1 = false; score1 = 0;
  jumping = false; 
  lastMoveTime = millis(); 
  moveInterval = 350; //how fast it starts

  wall1_x = 15; wall1_y = 1;
  wall3_x = 15 + random(6, 10); wall3_y = 1;

  tree_x = wall1_x + OBSTACLE_SPACE; tree_y = 1;
}

void Game2_init(){
  player2_x = 8; player2_y = 1;
  gameover2 = false; score2 = 0;

  wall2_x = 13; wall2_y = 0;
  projectile_x = 4; projectile_y = 0;
  
  lastFallTime = millis(); fallInterval = 600;
}

//=================== GAME 1 LOGIC ======================//
State Game1_update(){
  Display_clear();
  Input_update();
  
  if (Input_jumpPressed() && !jumping){
    Buzzer(3);
    jumping = true;
    jumpStartTime = millis();
  }
  
  if (gameover1){
    for (int i = 0; i < 5; i ++){
      Lights(4);
      Display_print("GAME OVER :(", 0,0);
      delay(300);
      Display_clear();
      delay(300);
    }
    
    // HIGH SCORE 
    if (score1 > highScore1){
      highScore1 = score1;
      EEPROM.put(EEPROM_HS1, highScore1);
      for (int i = 0; i < 5; i ++){
        Buzzer(4);
        Lights(4);
        Lights(3);
        Display_print("NEW HIGH SCORE", 1,0);
        Display_printint(highScore1, 6, 1);
        delay(300);
        Display_clear();
        delay(300);
      }
    }
    Game1_init();
    return STATE_GAME_MENU;
    
  } else {
    // Draw score
    Display_print("Score:", 8, 0);
    Display_printint(score1, 14, 0);

    // Clear previous positions
    Display_drawChar(' ', player1_x, player1_y);
    Display_drawChar(' ',wall1_x, wall1_y);

    unsigned long now = millis(); 
    if (now - lastMoveTime >= moveInterval){
      lastMoveTime = now;

      wall1_x--; wall3_x--; tree_x--;

      //Collision
      if (!jumping && (wall1_x == player1_x && wall1_y == player1_y ||
                          tree_x == player1_x && tree_y == player1_y||
                          wall3_x == player1_x && wall3_y == player1_y)){
        gameover1 = true;
      }
      
      if (score1 % 2 == 0 && moveInterval > MIN_MOVE_INTERVAL){
          moveInterval -= SPEEDUP_STEP;
      }
        
      if (wall1_x < 0){wall1_x = 15; score1++;}
      if (wall3_x < 0){wall3_x = 15 + random(8, 12); score1++;}
      if (tree_x < 0){tree_x = wall1_x + OBSTACLE_SPACE; score1++;}
      
    }
    
    // Jump logic
    player1_y = jumping?0:1;
    if(jumping && millis() - jumpStartTime >= jumpDuration) {jumping = false;}
    
    // Draw objects
    Display_drawChar(PLAYER, player1_x, player1_y);
    Display_drawChar(WALL, wall1_x, wall1_y);
    Display_drawChar(WALL, wall3_x, wall3_y);
    Display_drawChar(TREE, tree_x, tree_y);  
  }
  return STATE_GAME1;
}

//=================== GAME 2 LOGIC ======================//
State Game2_update(){
  Display_clear();
  Input_update();

  if (Input_rightPressed() && player2_x < 15){
    player2_x++;
  } else if (Input_leftPressed() && player2_x > 0){
    player2_x--;
  }
  
  if (gameover2){
    for (int i = 0; i < 5; i ++){
      Lights(4);
      Display_print("GAME OVER :(", 0,0);
      delay(300);
      Display_clear();
      delay(300);
    }
    Display_print("Score:", 4, 0);
    Display_printint(score2, 10, 0);
    delay(2000);

    // HIGH SCORE
    if (score2 > highScore2){
      highScore2 = score2;
      EEPROM.put(EEPROM_HS2, highScore2);
      
      for (int i = 0; i < 5; i ++){
        Buzzer(4);
        Lights(4);
        Lights(3);
        Display_print("NEW HIGH SCORE", 1,0);
        Display_printint(highScore2, 6, 1);
        delay(300);
        Display_clear();
        delay(300);
      }
    }
    
    Game2_init();
    return STATE_GAME_MENU;
    
  } else {
    
    unsigned long now = millis();
    if (now - lastFallTime >= fallInterval){
      lastFallTime = now;
      
      Display_drawChar(' ',wall2_x, wall2_y);
      Display_drawChar(' ',projectile_x, projectile_y);
      
      wall2_y++;
      if (wall2_y > 1){wall2_y = 0; wall2_x = random(0, 16); score2 ++;}
    
      projectile_y++;
      if (projectile_y > 1){projectile_y = 0; projectile_x = random(0, 16); score2 ++;}
       
      if (fallInterval > 150){fallInterval -= 10;}
    }

    // Clear previous player position
    Display_drawChar(' ', player2_x, player2_y);

    // Collision
    if (wall2_x == player2_x && wall2_y == player2_y || 
    projectile_x == player2_x && projectile_y == player2_y){
      gameover2 = true;
    }

    // Draw objects
    Display_drawChar(PLAYER, player2_x, player2_y);
    Display_drawChar(WALL, wall2_x, wall2_y);
    Display_drawChar(PROJECTILE, projectile_x, projectile_y);
    
  }
  return STATE_GAME2;
}

// ------------- High Scores Management -------------

void Game_loadHighScores(){
  EEPROM.get(EEPROM_HS1, highScore1);
  EEPROM.get(EEPROM_HS2, highScore2);

  if (highScore1 < 0 ||highScore1 > 9999){
    highScore1 = 0;
  }
  if (highScore2 < 0 || highScore2 > 9999){
    highScore2 = 0;
  }
}

void ResetHighScores(){
  highScore1 = 0;
  highScore2 = 0;
  EEPROM.put(EEPROM_HS1, highScore1);
  EEPROM.put(EEPROM_HS2, highScore2);
}
