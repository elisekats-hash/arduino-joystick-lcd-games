
#include "Display.h"
#include "Game.h"
#include "Input.h"
#include "Menu.h"

// --------------------- Timing ---------------------
int loopfast = 200;
int loopfaster = 50;

// --------------------- First-time Flags ---------------------
static bool startup = true;
static bool rules1 = true;
static bool rules2 = true;

// --------------------- State tracking ---------------------
State currentState = STATE_MAIN_MENU;
static State lastState = STATE_MAIN_MENU;

// --------------------- Setup ---------------------
void setup() {
  Display_init();
  Input_init();

  // Uncomment to reset high scores
  ResetHighScores();
  
  Game_loadHighScores();
  
}

// --------------------- Main loop ---------------------
void loop() {
  // --------------------- First-time startup ---------------------
  if (startup){
    Buzzer(1);
    Lights(1);
    Display_print("Welcome", 4, 0);
    delay(3000);
    Display_clear();
    startup = false;
  }

  // Update joystick inputs
  Input_update();

  // Initialize game if entering a new game state
  if (currentState != lastState){
    if (currentState == STATE_GAME1){
      Game1_init();
    }
    else if (currentState == STATE_GAME2){
      Game2_init();
    }
  }

  // --------------------- State logic ---------------------
  switch(currentState){
    
    case STATE_MAIN_MENU:
      currentState = MainMenu_update();
      break;

     case STATE_GAME_MENU:
      currentState = GameMenu_update();
      break;

    case STATE_GAME1:
      if (rules1){
        Display_clear();
        Display_print("Press down", 0, 0);
        Display_print("to jump", 0, 1);
        delay(3000);
        Display_clear();
        rules1 = false;
      }
      currentState = Game1_update();
      delay(loopfaster);
      break;

     case STATE_GAME2:
       if (rules2){
        Display_clear();
        Display_print("Avoid falling", 0, 0);
        Display_print("objects", 0, 1);
        delay(3000); 
        Display_clear();
        Display_print("by moving", 0, 0);
        Display_print("Left and Right", 0, 1);
        delay(3000);         
        Display_clear();
        rules2 = false;
      }
      currentState = Game2_update();
      delay(loopfaster);
      break;

     case STATE_EXIT:
      Exit_Menu();
      break;
  }

  // --------------------- Effects on state changes ---------------------
  if (currentState != lastState){
    switch(currentState){
      case STATE_GAME_MENU:
        Buzzer(3);
        Lights(3);
        break;
      case STATE_GAME1:
      case STATE_GAME2:
        Buzzer(3);
        Lights(3);
        break;
      case STATE_EXIT:
        Buzzer(2);
        Lights(2);
        break;

      default:
        break;
    }
    lastState = currentState;
  }
}
