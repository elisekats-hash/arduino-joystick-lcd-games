#ifndef MENU_H
#define MENU_H

// Menu/game states
enum State {
  STATE_MAIN_MENU,
  STATE_GAME_MENU,
  STATE_GAME1,
  STATE_GAME2,
  STATE_EXIT
};

// Menu update functions
State MainMenu_update();
State GameMenu_update();
void Exit_Menu();

#endif
