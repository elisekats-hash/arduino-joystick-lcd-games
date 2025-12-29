#include "Menu.h"
#include "Display.h"
#include "Input.h"

// -------------------- Menu variables --------------------
// Game menu
int gameCursor = 0;
bool gameMenu = false;

// Main menu
int mainCursor = 0; 
bool mainMenu = false;

// Exit menu
static bool exitshow = false;

// -------------------- Main Menu --------------------
State MainMenu_update(){
    static int lastCursor = -1;
    
    if (!mainMenu){
      Display_clear();
      Display_print("Main Menu-Scroll", 0,  0);
      Display_print("Game Menu", 0, 1);
      Display_drawChar(WALL, 0,1);
      mainMenu = true;
      lastCursor = -1;
    }

    // Move cursor
    if (Input_upPressed() || Input_downPressed()){
      mainCursor ^= 1; //Toggle between 0 and 1
    }

    // Redraw menu row if cursor changed
    if (mainCursor != lastCursor){
      Display_clear_row(1);
      Display_drawChar(WALL, 0, 1);
      Display_print(mainCursor == 0?"Game Menu": "Exit", 1, 1);
      lastCursor = mainCursor;
    }

    // Selection
    if (Input_jumpPressed()){
      mainMenu = false;
      return (mainCursor == 0)? STATE_GAME_MENU:STATE_EXIT;
    }
    return STATE_MAIN_MENU;
  }

// -------------------- Game Menu --------------------
State GameMenu_update(){
   static int lastCursor = -1;
   
   if (!gameMenu){
     Display_clear();
     Display_print("Game Menu-Scroll", 0, 0);
     Display_print("Game 1", 0, 1);
     Display_drawChar(WALL, 0, 1);
     gameMenu = true;
     lastCursor = -1;
   }

   // Move cursor
   if (Input_upPressed()){
     gameCursor = (gameCursor +2)%3;
   }
   if (Input_downPressed()){
     gameCursor = (gameCursor + 1)%3;
   }
   
   // Redraw menu row if cursor changed
   if (gameCursor != lastCursor){
     Display_clear_row(1);
     Display_drawChar(WALL, 0, 1);
    
     switch(gameCursor){
      case 0: Display_print("Game 1", 1, 1); break;
      case 1: Display_print("Game 2", 1, 1); break;
      default: Display_print("Back", 1, 1); break;
     }
     lastCursor = gameCursor;
   }
   
    // Selection
   if (Input_jumpPressed()){
     gameMenu = false;

     switch (gameCursor){
      case 0: return STATE_GAME1;
      case 1: return STATE_GAME2;
      default: return STATE_MAIN_MENU;
     }
   }
   return STATE_GAME_MENU;
}

// -------------------- Exit Menu --------------------
void Exit_Menu(){
  if (!exitshow){
    Display_clear();
    Display_print("Exiting...Bye", 0, 0);
    Display_drawChar(SPARE, 14, 0);
    exitshow = true;
  }
}
