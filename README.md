# Joystick LCD Mini Games (Arduino)

A mini game console embedded system built on Arduino, featuring two joystick-controlled games displayed on 16x2 LCD screen. The system includes sound effects, LED indicators, and persistent high score storage using EEPROM. The project demonstrates real-time input handling, finite state machines, timing-based game logic, and modular embedded software design.

--------------------------------------------------

## Hardware Used

- Arduino board UNO R3
- 16x2 LCD display (LiquidCrystal compatible)
- Analog joystick (X, Y, Push Button)
- Passive buzzer
- Red & green LEDs
- Potentiometer
- Breadboard and jumper wires

--------------------------------------------------

## Usage

### Controls
- **Move joystick**: Navigate menus and control game characters
- **Press joystick button**: Select menu options and perform in-game actions

### Menu Navigation
- Use the joystick to scroll through menu options
- Press the joystick button to select

--------------------------------------------------

## High Scores

- High scores for both games are saved to EEPROM
- Scores persist between power cycles
- To reset high scores, uncomment ResetHighScores() in the setup() function

--------------------------------------------------

## Games Included

### Game 1: Jumper
**Objective**: Jump over obstacles to achieve the highest score
- **Controls**: Press joystick down to jump
- **Gameplay**: Obstacles move faster over time
- **Scoring**: Points increase as obstacles are successfully avoided

### Game 2: Falling Objects
**Objective**: Avoid falling objects by moving left and right
- **Controls**: Move joystick left/right to dodge objects
- **Gameplay**: Falling speed increases over time
- **Scoring**: Based on survival time and avoided objects

--------------------------------------------------

## Features
- Finite State Machine (Main Menu, Game Menu, Games, Exit)
- Non-blocking timing using millis()
- Edge-detected joystick input (pressed vs held)
- EEPROM high score persistence
- Custom LCD characters
- Sound effects and melodies using passive buzzer
- LED visual feedback for game events

--------------------------------------------------

## File Structure
- JoystickLCDGame.ino – Main program loop and state control
- Game.cpp / Game.h – Game logic and high score handling
- Menu.cpp / Menu.h – Menu navigation system
- Input.cpp / Input.h – Joystick input handling
- Display.cpp / Display.h – LCD, LEDs, and buzzer control
- Pitches.h – Sound frequency definitions

--------------------------------------------------

### Pin Connections

- **LCD**: Standard LiquidCrystal pin connections
- **Joystick**:
  - X-axis: Analog pin A0
  - Y-axis: Analog pin A1
  - Button: Digital pin 2

- **Buzzer**: Digital pin 3

- **LEDs**:
  - Green LED: Digital pin 5
  - Red LED: Digital pin 4

--------------------------------------------------

## Software Requirements

- Arduino IDE (version 1.8.0 or later)
- LiquidCrystal library (included with Arduino IDE)
- EEPROM library (included with Arduino IDE)

## Installation

1. **Open** JoystickLCDGame.ino in Arduino IDE
2. **Connect** Arduino board to computer
3. **Select** the correct board and port
4. **Upload** the sketch

## Acknowledgments

- Built using Arduino platform
- Inspired by classic arcade games
- Custom LCD characters for enhanced gameplay
