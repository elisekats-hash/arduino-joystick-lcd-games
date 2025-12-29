#include "Input.h"
#include <Arduino.h>

// Raw joystick readings
static int x_val = 512;
static int y_val = 512;
static bool sw_pressed = false;

// Last state for one press detection
static bool lastup = false;
static bool lastdown = false;
static bool lastjump = false;
static bool lastright = false;
static bool lastleft = false;

void Input_init(){
  pinMode(JOY_SW, INPUT_PULLUP);
}

void Input_update(){
  x_val = analogRead(JOY_X);
  y_val = analogRead(JOY_Y);
  sw_pressed = (digitalRead(JOY_SW)==LOW);
}

// Continous input
bool Input_right(){
  return x_val < JOY_RIGHT_THRESH;
}
bool Input_left(){
  return x_val > JOY_LEFT_THRESH;
}
bool Input_up(){
  return y_val < JOY_UP_THRESH;
}
bool Input_down(){
  return y_val > JOY_DOWN_THRESH;
}
bool Input_jump(){
  return sw_pressed;
}

// One press input (rising edge)
bool Input_upPressed(){
  bool current = Input_up();
  bool pressed = current && !lastup;
  lastup = current;
  return pressed;
}

bool Input_downPressed(){
  bool current = Input_down();
  bool pressed = current && !lastdown;
  lastdown = current;
  return pressed;
}

bool Input_jumpPressed(){
  bool current = Input_jump();
  bool pressed = current && !lastjump;
  lastjump = current;
  return pressed;
}

bool Input_rightPressed(){
  bool current = Input_right();
  bool pressed = current && !lastright;
  lastright = current;
  return pressed;
}

bool Input_leftPressed(){
  bool current = Input_left();
  bool pressed = current && !lastleft;
  lastleft = current;
  return pressed;
}
