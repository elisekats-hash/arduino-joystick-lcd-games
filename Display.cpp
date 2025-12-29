/* For outputs*/
#include "Display.h"
#include "Pitches.h"

// === LCD setup ===
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// === Custom characters === 
byte wallChar[8] = {
  B00000,B00000,B11111,B11111,B11111,B11111,B11111,B11111,
};
byte projectileChar[8] = {
  B00000,B00100,B01110,B11111,B01110,B00100,B00000,B00000,
};
byte playerChar[8] = {
  B01110,B01110,B00100,B11111,B11111,B10101,B01010,B10001,
};
byte enemyChar[8] = {
  B01010,
  B01110,
  B01110,
  B00100,
  B11111,
  B11111,
  B01110,
  B01010,
};
byte treeChar[8] = {
  B00100,B00110,B01110,B01110,B11111,B00100,B00100,B00100,
};
byte effectChar[8] = {
  B10001,B11011,B01010,B00100,B01010,B11011,B10001,B00000,
};
byte statusChar[8] = {
  B00000,B00000,B00000,B11011,B11111,B01110,B00100,B00000,
};
byte spareChar[8] = {
  B00000,B00000,B00000,B01010,B00000,B10001,B01110,B00000,
};

// === Buzzer melodies ===
static const int melody1[3] = {NOTE_C5, NOTE_D5, NOTE_E5};
static const int melody2[3] = {NOTE_E5, NOTE_D5, NOTE_C5};
static const int melody3[7] = {
    NOTE_C5,
    NOTE_D5,
    NOTE_E5,
    NOTE_G5,
    NOTE_E5,
    NOTE_G5,
    NOTE_C6
};

// === Initialization ===
void Display_init(){
  lcd.begin(LCD_COLS, LCD_ROWS);

  lcd.createChar(WALL, wallChar); //1
  lcd.createChar(PROJECTILE, projectileChar); //2
  lcd.createChar(PLAYER, playerChar); //3
  lcd.createChar(ENEMY, enemyChar); //4
  lcd.createChar(TREE, treeChar); //5
  lcd.createChar(EFFECT, effectChar); //6
  lcd.createChar(STATUS, statusChar); //7
  lcd.createChar(SPARE, spareChar);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  lcd.clear();
}

// === Drawing functions ===
void Display_drawChar(byte ch, int x, int y){
  lcd.setCursor(x, y);
  lcd.write(ch);
}

void Display_print(const char*text, int x, int y){
  lcd.setCursor(x, y);
  lcd.print(text);
}

void Display_printint(int value, int x, int y){
  lcd.setCursor(x, y);
  lcd.print(value);
}

void Display_clear(){
  lcd.clear();
}

void Display_clear_row(int y){
  lcd.setCursor(0, y);
  lcd.print("                "); // 16 spaces
}

// === Buzzer ===
void Buzzer(int sound){
  switch(sound){
    case 1:
      for (int thisNote = 0; thisNote < 3; thisNote++){
        tone(BUZZER, melody1[thisNote], 300);
        delay(100);
      }
      break;
    case 2:
      for (int thisNote = 0; thisNote <3; thisNote++){
          tone(BUZZER, melody2[thisNote], 300);
          delay(100);
      }
      break;
    case 3:
      tone(BUZZER, NOTE_C6, 50);
      break;
    case 4: // HIGH SCORE
      for (int thisNote = 0; thisNote < 7; thisNote++) {
        tone(BUZZER, melody3[thisNote], 70);
        delay(100);
      }
      break;
  }
}

// === Lights ===
void Lights(int pattern){
  switch(pattern){
    case 1: // START pattern
      for (int i = 0; i < 3; i++){
        digitalWrite(LED_G, HIGH);
        delay(100);
        digitalWrite(LED_R, HIGH);
        delay(50);
        digitalWrite(LED_G, LOW);
        delay(100);
        digitalWrite(LED_R, LOW);
        delay(100);
      }
      break;
    case 2: // EXIT pattern
      for (int count = 5; count > 0; count --){
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_R, HIGH);
        delay(50);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_R, LOW);
        delay(count*100);
      }
      break;
    case 3: // GREEN
      digitalWrite(LED_G, HIGH);
      delay(50);
      digitalWrite(LED_G, LOW);
      break;
    case 4: // RED
      digitalWrite(LED_R, HIGH);
      delay(100);
      digitalWrite(LED_R, LOW);
      break;
  }

  
}
