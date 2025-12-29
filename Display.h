#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include <Arduino.h>

// LCD Characters
#define WALL 0
#define PROJECTILE 1
#define PLAYER 2
#define ENEMY 3
#define TREE 4
#define EFFECT 5
#define STATUS 6
#define SPARE 7

// Pins
#define BUZZER 3
#define LED_G 5
#define LED_R 4

// LCD size
#define LCD_COLS 16
#define LCD_ROWS 2

// Initialization
void Display_init();

// Drawing
void Display_drawChar(byte ch, int x, int y);
void Display_print(const char*test, int x, int y);
void Display_printint(int value, int x, int y);
void Display_clear();
void Display_clear_row(int y);

// Game effects
void Buzzer(int sound);
void Lights(int pattern);
void Buzzer_reset();

#endif
