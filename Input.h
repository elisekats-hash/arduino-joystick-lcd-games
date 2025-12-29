#ifndef INPUT_H
#define INPUT_H

// Pins
#define JOY_X A2
#define JOY_Y A1
#define JOY_SW 2

// Joystick threshold values
#define JOY_LEFT_THRESH 700
#define JOY_RIGHT_THRESH 300
#define JOY_UP_THRESH 300
#define JOY_DOWN_THRESH 700

// Intialize and update input values
void Input_init();
void Input_update();

// Continous directional input
bool Input_left();
bool Input_right();
bool Input_up();
bool Input_down();
bool Input_jump();

// One press detection
bool Input_upPressed();
bool Input_downPressed();
bool Input_jumpPressed();
bool Input_rightPressed();
bool Input_leftPressed();

#endif
