# Sbutton

[![arduino-library-badge](https://www.ardu-badge.com/badge/Sbutton.svg?)](https://www.ardu-badge.com/Sbutton)
![License](https://img.shields.io/badge/License-MIT-blue)
![Tests](https://img.shields.io/github/languages/top/duinolibs/Sbutton)
![Tests](https://img.shields.io/badge/version-0.1.2-blue)
![Tests](https://img.shields.io/github/last-commit/duinolibs/Sbutton)
## Comands
```cpp
Sbutton btn (pin, pinmode, normstate); //button initialization
SbuttonBase                 // only clicks
SbuttonMulticlick           // only multiclick
SbuttonHold                 // hold and double click
Sbutton                     // all functions

void tick();                // obligatory function

bool isPressed();            //(all)returns true if button is pressed
bool isClicked();            //(all)returns true if button is clicked
bool isReleased();           //(all)returns true if button is released
bool isHeld();               //(-B,M)returns true if button is pressed in timeout
bool isHold();               //(-B,M)returns true if button is pressed after timeout
bool hasSingle();            //(-B)returns true if button is clicked once
bool hasDouble();            //(-B)returns true if button is clicked twice
bool hasTriple();            //(-B,H)returns true if button is clicked three times

uint8_t hasClicks();         //(-B,H)returns clicks 
uint8_t hasClicksWithHeld(); //(-B,H,M)returns clicks before pressing
uint8_t hasClicksWithHold(); //(-B,H,M)returns clicks before holding
```
## Using example
```cpp

#include "SButton.h"

Sbutton btn (3, 0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  btn.tick();

  if (btn.isPressed())
    digitalWrite(13, 1);
  else
    digitalWrite(13, 0);

  if (btn.isClicked())
    Serial.print("Clicked ");
  
  if (btn.isReleased())
    Serial.print("Released ");
  
  if (btn.isHeld())
    Serial.print("Hold " + String(btn.hasClicksWithHeld()) + "\n");
  
  if (btn.hasClicks())
    Serial.print("Clicks:" + String(btn.hasClicks()) + "\n");
}

```
