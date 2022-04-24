# Sbutton

[![arduino-library-badge](https://www.ardu-badge.com/badge/Sbutton.svg?)](https://www.ardu-badge.com/Sbutton)
![License](https://img.shields.io/badge/License-MIT-blue)
![Tests](https://img.shields.io/github/languages/top/duinolibs/Sbutton)
![Tests](https://img.shields.io/badge/version-0.0.5-blue)
![Tests](https://img.shields.io/github/last-commit/duinolibs/Sbutton)

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
  
  if (btn.isHeld())
    Serial.print("Hold " + String(btn.hasClicksWithHeld()) + "\n");
  
  if (btn.hasClicks())
    Serial.print("Clicks:" + String(btn.hasClicks()) + "\n");
}

```
